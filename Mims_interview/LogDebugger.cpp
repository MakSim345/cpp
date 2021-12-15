/**
 * Copyright (c) 2009-2014 General Electric Company. All rights reserved.
 */
#include "MiMS/Config/LogDebugger.hpp"
#include "MiMS/Actuator/SensorVoltageControl.hpp"
#include "MiMS/Config/ActuatorCfg.hpp"
#include "MiMS/Config/FlashBootEnv.hpp"
#include "MiMS/Config/MemoryCfg.hpp"
#include "MiMS/Config/MiMSSensorCfg.hpp"
#include "MiMS/Config/PMemCfg.hpp"
#include "MiMS/Main/Threads.hpp" // thread stack size & priority got from here.
#include "Msf/Common/Log/DiagnosticsLog.hpp"
#include "Msf/Common/Log/LogReader.hpp"
#include "Msf/Common/Log/TraceManager.hpp"
#include "Msf/Common/Os/Functors/MemberFunctor1.hpp"
#include "Msf/Common/Os/OsSystemTime.hpp"
#include "Msf/Common/Os/SmxV4/Smx.hpp"
#include "Msf/Common/Primitives/Time/UnixTime.hpp"
#include "Msf/Common/SystemState/SystemEnvironment.hpp"
#include "Msf/Hardware/SerialComm/SerialChannelAbs.hpp"
#include "Msf/ParamAcq/ParAcqToolkit/PMem/PMemRecordBuilder.hpp"
#if OS_DEF==SMX_OS
#include "../XFD/nortest.h"
#ifdef MIMS_REWORK_NEEDED_SMXFLOG
#include "../XFL/smxflog.h"
#endif
#include "Msf/Common/SystemMonitor/SystemMonitor.hpp"
#ifdef MIMS_REWORK_NEEDED_SYSTEMSTARTUP
#include "Msf/Common/SystemMonitor/SystemStartup.hpp"
#endif
#endif

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>

extern bool isOutputProfileEnabled;  //lint -esym(526,isOutputProfileEnabled) from main.c

// Using Declarations
using Msf::ParAcqToolkit::PMemRecordBuilder;

namespace MiMS {

/** Command enumeration. */
enum
{
    LOG_DBG_CMD_HELP,                   // 00
    LOG_DBG_CMD_STOP,                   // 01
    LOG_DBG_CMD_ERASE_0,                // 02
    LOG_DBG_CMD_ERASE_1,                // 03
    LOG_DBG_CMD_READ_0_1000,            // 04
    LOG_DBG_CMD_READ_1_1000,            // 05
    LOG_DBG_CMD_READ_0_ALL,             // 06
    LOG_DBG_CMD_READ_1_ALL,             // 07
    LOG_DBG_CMD_WRITE_0,                // 08
    LOG_DBG_CMD_WRITE_1,                // 09
    LOG_DBG_CMD_WRITE_0_2000,           // 10
    LOG_DBG_CMD_WRITE_1_9999,           // 11
    LOG_DBG_CMD_PRINT,                  // 12
    LOG_DBG_CMD_VERB_OFF,               // 13
    LOG_DBG_CMD_VERB_ON,                // 14
    LOG_DBG_CMD_GETTIME,                // 15
    LOG_DBG_CMD_RUNTIME,                // 16
    LOG_DBG_CMD_RESCNT,                 // 17
    LOG_DBG_CMD_MANRES,                 // 18
    LOG_DBG_CMD_MAKETRAP,               // 19
    LOG_DBG_CMD_LIST_CPU,               // 20
    LOG_DBG_CMD_LIST_MIMS_SENSOR,       // 21
    LOG_DBG_CMD_LIST,                   // 22
    LOG_DBG_CMD_RESET_CPU,              // 23
    LOG_DBG_CMD_RESET_MIMS_SENSOR,      // 24
    LOG_DBG_CMD_RESET,                  // 25
    LOG_DBG_CMD_SAVE_CPU,               // 26
    LOG_DBG_CMD_SAVE_MIMS_SENSOR,       // 27
    LOG_DBG_CMD_SAVE,                   // 28
    LOG_DBG_CMD_CHANGE_EE_HEX,          // 29
    LOG_DBG_CMD_CHANGE_EE_DEC,          // 30
    LOG_DBG_CMD_RESET_EE,               // 31
    LOG_DBG_CMD_SET_WARM,               // 32
    LOG_DBG_CMD_CLEAR_WARM,             // 33
    LOG_DBG_CMD_ENABLE_TRACE_KEY,       // 34
    LOG_DBG_CMD_DISABLE_TRACE_KEY,      // 35
    LOG_DBG_CMD_ENABLE_PROFILING,       // 36
    LOG_DBG_CMD_DISABLE_PROFILING,      // 37
    LOG_DBG_CMD_PRINT_ENVVARS,          // 38
    LOG_DBG_CMD_OVERFLOW_STACK,         // 39
    LOG_DBG_CMD_OVERFLOW_HEAP,          // 40
    LOG_DBG_CMD_LAMP_VOLTAGE_INC,       // 41
    LOG_DBG_CMD_LAMP_VOLTAGE_DEC,       // 42
    LOG_DBG_CMD_SENSORCOMM_DIAGNOSTICS, // 43
    LOG_DBG_CMD_TEST_NORIO,             // 44
    LOG_DBG_CMD_TEST_NORIO_PERF,        // 45
    LOG_DBG_CMD_MEMORY_USAGE,           // 46
    LOG_DBG_CMD_NR_OF_CMDS              // 47
};

struct StringPair
{
    const char* pNameStrM;
    const char* pDescriptionStrM;
};

/** Command {name,description} pairs. */
static const StringPair aCommandsS[LOG_DBG_CMD_NR_OF_CMDS] =
{
    /* 00 */ { "help"        , "show this help (the list of commands)"                            },
    /* 01 */ { "stop"        , "stop the current long reading or writing"                         },
    /* 02 */ { "erase 0"     , "erase partition 0 (software error log)"                           },
    /* 03 */ { "erase 1"     , "erase partition 1 (diagnostics log)"                              },
    /* 04 */ { "read 0 1000" , "read 1000 logs from partition 0 (software error log)"             },
    /* 05 */ { "read 1 1000" , "read 1000 snapshots from partition 1 (diagnostics log)"           },
    /* 06 */ { "read 0 all"  , "read all logs from partition 0 (software error log)"              },
    /* 07 */ { "read 1 all"  , "read all snapshots from partition 1 (diagnostics log)"            },
    /* 08 */ { "write 0"     , "write one software log entry on partition 0"                      },
    /* 09 */ { "write 1"     , "write one diagnostic log entry on partition 1"                    },
    /* 10 */ { "write 0 2000", "write 2000 software log entries on partition 0"                   },
    /* 11 */ { "write 1 9999", "write 9999 bin-snapshots on partition 1"                          },
    /* 12 */ { "print"       , "print the current smxFLog debugging data"                         },
    /* 13 */ { "verbose off" , "disable smxFLog debugging data after each log"                    },
    /* 14 */ { "verbose on"  , "enable smxFLog debugging data after each log"                     },
    /* 15 */ { "time"        , "return current time"                                              },
    /* 16 */ { "runtime"     , "gets current and whole CPU and total sensors run-time"            },
    /* 17 */ { "rescnt"      , "clear the reset-counter and runtime from flash/EEPROM"            },
    /* 18 */ { "manres"      , "force a manual watchdog reset"                                    },
    /* 19 */ { "maketrap"    , "force a trap exception, for testing"                              },
    /* 20 */ { "eelist cpu"  , "list all CPU Flash values"                                        },
    /* 21 */ { "eelist ms"   , "list all MiMS Sensor flash values"                                },
    /* 22 */ { "eelist"      , "list given PMem values. Cmd format = \"eelist <pmem>_<rec>\""     },
    /* 23 */ { "eereset cpu" , "reset all CPU Flash values to default values"                     },
    /* 24 */ { "eereset ms"  , "reset all MiMS Sensor flash values to default values"             },
    /* 25 */ { "eereset"     , "reset given PMem values to default values. Cmd format = \"eereset <pmem>_<rec>\"" },
    /* 26 */ { "eesave cpu"  , "save all CPU Flash values"                                        },
    /* 27 */ { "eesave ms"   , "save all MiMS Sensor flash values"                                       },
    /* 28 */ { "eesave"      , "save given PMem record. Cmd format = \"eesave <pmem>_<rec>\""     },
    /* 29 */ { "eeh"         , "change one eeprom variable. Cmd format = \"eeh <pmem>_<rec> 4 08a49022\""  },
    /* 30 */ { "eed"         , "change one eeprom variable. Cmd format = \"eed <pmem>_<rec> 4 145002530\"" },
    /* 31 */ { "eer"         , "reset one eeprom variable to default. Cmd format = \"eed <pmem>_<rec> 4\"" },
    /* 32 */ { "setwarm"     , "set warm start pattern in RAM"                                    },
    /* 33 */ { "clearwarm"   , "remove warm start pattern from RAM"                               },
    /* 34 */ { "enable tr"   , "enable  the traces by given key. Cmd format = enable tr <trace_key>"   },
    /* 35 */ { "disable tr"  , "disable the traces by given key. Cmd format = disable tr <trace_key>"  },
    /* 36 */ { "prof on"     , "enable profiling"                                                       },
    /* 37 */ { "prof off"    , "disable profiling"                                                      },
    /* 38 */ { "printenv"    , "print enviroment variables"                                                      },
    /* 39 */ { "overflow stack"  , "overflow the stack, meant for unit testing."  },
    /* 40 */ { "overflow heap"  , "overflow the heap, meant for unit testing."  },
    /* 41 */ { "isv"         , "increase sensor voltage target by 100 mV"  },
    /* 42 */ { "dsv"         , "decrease sensor voltage target by 100 mV"  },
    /* 43 */ { "sensorcomm diagnostics", "print current sensor communication serial port diagnostics" },
    /* 44 */ { "testnorio"     , "test flash erase, write and read (overwrites 512-1024kB)" },
    /* 45 */ { "testnorioperf" , "test flash read and write performance (overwrites 512-1024kB)" },
    /* 46 */ { "memuse"      , "print memory usage" }
};

LogDebugger* LogDebugger::pInstanceM = 0;

// Lint silencing is needed because there is less code compiling in the MSVC/lint
// compilation than on the real target.

LogDebugger* LogDebugger::createInstance(
    Msf::Os::FunctorThread& rWorkerThreadP,
    PMemCfg& rPMemCfgP,
    Msf::SerialComm::SerialChannelAbs* pSerialPortP,
    FlashBootEnv& rFlashBootEnvarsP,
    ActuatorCfg& rActuatorCfgP)
{
    if (!pInstanceM)
    {
#if  (OS_DEF==SMX_OS)
        static LogDebugger instance(rWorkerThreadP, rPMemCfgP, pSerialPortP, rFlashBootEnvarsP, rActuatorCfgP);
        pInstanceM = &instance;

#ifdef MIMS_REWORK_NEEDED_SMXFLOG
        sfl_GetDbgCfgData(Msf::Log::LOG_MAIN_TRACES, true);  // logs
        sfl_GetDbgCfgData(Msf::Log::LOG_BINARY_DIAG, true);  // snaps
        sfl_GetDbgCfgData(Msf::Log::LOG_CPU_RT_DATA, true);  // new cpu_rt_data
        sfl_GetDbgHandleData(Msf::Log::LOG_MAIN_TRACES, true);  // logs
        sfl_GetDbgHandleData(Msf::Log::LOG_BINARY_DIAG, true);  // snaps
        sfl_GetDbgHandleData(Msf::Log::LOG_CPU_RT_DATA, true);  // new cpu_rt_data
#endif
#endif
    }
    return pInstanceM;
} //lint !e1762 !e715 !e1764 "function could be made const" "rWorkerThreadP not referenced and could be made const"

LogDebugger* LogDebugger::getInstance()
{
    // should be created before
    return pInstanceM;
}

LogDebugger::LogDebugger(
    Msf::Os::FunctorThread& rWorkerThreadP,
    PMemCfg& rPMemCfgP,
    Msf::SerialComm::SerialChannelAbs* pSerialPortP,
    FlashBootEnv& rFlashBootEnvarsP,
    ActuatorCfg& rActuatorCfgP
) : Msf::Os::OsThreadAbs(LOGDEBUGGER_THREAD_PRIORITY, LOGDEBUGGER_THREAD_STACKSIZE, "LogDebugger", 0, false),
    startTimeM(0),
    nRepeatCntM(0),
    bRequestStoppingM(false),
    rWorkerThreadM(rWorkerThreadP),
    rPMemCfgM(rPMemCfgP),
    pSerialPortM(pSerialPortP),
    rFlashBootEnvarsM(rFlashBootEnvarsP),
    rActuatorCfgM(rActuatorCfgP)
{
}

LogDebugger::~LogDebugger()
{
}

void LogDebugger::startThread()
{
#if  (OS_DEF==SMX_OS)
    static bool bStarted = false;
    if (!bStarted)
    {
        bStarted = true;
        Msf::Os::OsThreadAbs::start();
    }
#endif
} //lint !e1762 "function could be made const"

void LogDebugger::entry()
{
    //If driver is not available we cannot start the LogDebugger.
    if (NULL == pSerialPortM)
    {
        return;
    }

    MSF_LOG_INFO("!!!!!!!!    LogDebugger active (type help)    !!!!!!!!");

    /** A buffer storing the raw input from the terminal. */
    char aBuff[INPUT_BUFF_SIZE] = {0};
    char aCmd[INPUT_BUFF_SIZE] = {0};
    size_t head = 0;
    size_t cmdIndex = 0;
    size_t actualReadCount = 0;

    while(!isTerminationRequested())
    {
        //Receive Data
        pSerialPortM->read(actualReadCount, aBuff, INPUT_BUFF_SIZE);
        //Update the index with the new data
        head = actualReadCount;

        //Process the received data
        for(size_t i = 0; i < head; ++i)
        {
            switch(aBuff[i])
            {
                //We found end line char. Let's save the command.
                case CR_CHAR:
                case LF_CHAR:
                    {
                        //Append the null termination
                        aCmd[cmdIndex++] = 0;
                        //Output a new line just to simulate execution
                        cout << endl;
                        //Process the command
                        if (strlen(aCmd) > 2)
                        {
                            handleCommand(aCmd);
                        }
                        //Update the counters
                        cmdIndex = 0;
                    }
                  break;
                //This is a backspace char
                case BS_CHAR:
                    {
                        if (cmdIndex>0)
                        {
                            //Echo the backspace
                            cout << (char)BS_CHAR << flush;
                            //Echo space
                            cout << (char)SPACE_CHAR << flush;
                            //Echo the backspace
                            cout << (char)BS_CHAR << flush;
                            --cmdIndex;
                        }
                    }
                  break;
                //This is a normal char. Save it and continue.
                default:
                    {
                        if ((aBuff[i] > 0) && (aBuff[i] < 127))
                        {
                           if (cmdIndex < INPUT_BUFF_SIZE)
                           {
                               //Copy the char.
                               memcpy(aCmd+cmdIndex, &aBuff[i], 1);
                               //Echo the char
                               cout << aBuff[i] << flush;
                               ++cmdIndex;
                           }
                           else
                           {
                               printf("\nCommand to long. Drop the command\n");
                               //Clear what we had until now
                               memset(aCmd, 0, INPUT_BUFF_SIZE);
                               cmdIndex = 0;
                           }
                        }
                        //We received some wrong char's
                        else
                        {
                            //Clear what we had until now
                            memset(aCmd, 0, INPUT_BUFF_SIZE);
                            cmdIndex = 0;
                        }
                    }
                  break;
            }
        }
    }
}

void LogDebugger::handleCommand(const char* pCmdP)
{
    //Sanity check
    MSF_ASSERT(NULL != pCmdP);

    bool bProcessed = false;
    for(int n = 0; n < ELEMENTS(aCommandsS); ++n)
    {
        int cmp = -1;

        //For trace commands we have to use this solution since this command
        //contain different parameters. First we identify if command is present
        //in string and we will extract and parse the parameters later.
        if ((LOG_DBG_CMD_ENABLE_TRACE_KEY == n) || (LOG_DBG_CMD_DISABLE_TRACE_KEY == n))
        {
            const char* pCmpRes = strstr(pCmdP, aCommandsS[n].pNameStrM);
            if (NULL != pCmpRes) { cmp = 0; }
        }
        else
        {
            cmp = strcmp(pCmdP, aCommandsS[n].pNameStrM);
        }

        if (cmp == 0)
        {
            // Input recognized
            if (n == LOG_DBG_CMD_HELP)
            {
                cout << endl << "Supported commands:" << endl;
                for(int i = 0; i < ELEMENTS(aCommandsS); ++i)
                {
                    unsigned int len = strlen(aCommandsS[i].pNameStrM);
                    cout << aCommandsS[i].pNameStrM;

                    enum { LOG_DBG_CMD_MAX_LEN = 16 };
                    if (len < LOG_DBG_CMD_MAX_LEN)
                    {
                        for(unsigned int j = 0; j < LOG_DBG_CMD_MAX_LEN - len; ++j)
                        {
                            cout << " ";
                        }
                    }
                    cout << "  -  " << aCommandsS[i].pDescriptionStrM << endl;
                }
                cout << endl;
            }
            else if (n == LOG_DBG_CMD_STOP)
            {
                if (nRepeatCntM > 0)
                {
                    cout << " Stopping... " << endl << endl;
                    bRequestStoppingM = true;
                }
            }
            else if (n == LOG_DBG_CMD_PRINT)
            {
#if OS_DEF==SMX_OS
#ifdef MIMS_REWORK_NEEDED_SMXFLOG
                sfl_GetDbgCfgData(Msf::Log::LOG_MAIN_TRACES, true);  // logs
                sfl_GetDbgCfgData(Msf::Log::LOG_BINARY_DIAG, true);  // snaps
                sfl_GetDbgCfgData(Msf::Log::LOG_CPU_RT_DATA, true);  // new cpu_data
                sfl_GetDbgHandleData(Msf::Log::LOG_MAIN_TRACES, true);  // logs
                sfl_GetDbgHandleData(Msf::Log::LOG_BINARY_DIAG, true);  // snaps
                sfl_GetDbgHandleData(Msf::Log::LOG_CPU_RT_DATA, true);  // new cpu_data
#endif
#endif
            }
            else if (n == LOG_DBG_CMD_VERB_OFF)
            {
#if OS_DEF==SMX_OS
#ifdef MIMS_REWORK_NEEDED_SMXFLOG
                sfl_Verbose(false);
#endif
#endif
            }
            else if (n == LOG_DBG_CMD_VERB_ON)
            {
#if OS_DEF==SMX_OS
#ifdef MIMS_REWORK_NEEDED_SMXFLOG
                sfl_Verbose(true);
#endif
#endif
            }
            else if (n == LOG_DBG_CMD_RUNTIME)
            {
#if OS_DEF==SMX_OS
                unsigned long secs = Msf::Os::OsSystemTime::getSystemTimeInSecs();
                unsigned int mins = (secs / 60);
                unsigned int hrs = (mins / 60);
                unsigned int days = (hrs / 24);
                secs %= 60;
                mins %= 60;
                hrs %= 24;
                cout << "  Current power-on for ";
                if (days > 0)
                {
                    cout << dec << days << " days ";
                }
                cout << "(h:m:s) " << dec << setw(2) << setfill('0') << hrs << ":" << setw(2)       \
                    << setfill('0') << mins << ":" << setw(2) << setfill('0') << secs << "." << endl;

                unsigned long nHours = rPMemCfgM.cpuPmemDataM.uptimeCounterM.nValueM;
                unsigned long nResets = rPMemCfgM.cpuPmemDataM.startupCounterM.nValueM;
                unsigned long nDays = nHours / 24;
                nHours %= 24;
                /// @todo Should sensor runtime also be displayed here?
                cout << "  Nr of resets=" << nResets                                               \
                    << ", Total CPU runtime (d-h) "                                                \
                    << setw(2) << setfill('0') << nDays << "-"                                     \
                    << setw(2) << setfill('0') << nHours << "." << endl;
#endif  // SMX_OS
            }
            else if (n == LOG_DBG_CMD_GETTIME)
            {
#if OS_DEF==SMX_OS
                char buffer[64];
                time_t rawtime = Msf::UnixTime::now().getWallTimeInSeconds(Msf::UnixTime::STATIC_TIME);
                tm* pTm = localtime(&rawtime);
                unsigned int written = strftime(buffer, 64, "%Y-%b-%d %H:%M:%S", pTm);
                if (written > 0)
                {
                    cout << buffer << flush << endl;
                }
#endif
            }
            else if (n == LOG_DBG_CMD_RESCNT)
            {
#if OS_DEF==SMX_OS
                /*reset startup counter*/
                rPMemCfgM.cpuPmemDataM.uptimeCounterM.setValue(0);
                rPMemCfgM.cpuPmemDataM.startupCounterM.setValue(0);
                rPMemCfgM.cpuPmemDataM.asyncUnprotectingWriteRecordsToChip();
                cout << "CPU Flash startup and runtime counters cleared!" << flush << endl;
#endif
            }
            else if (n == LOG_DBG_CMD_MANRES)
            {
#if OS_DEF==SMX_OS
                Msf::SystemMonitor::SystemMonitor::resetSystemNow("Manual watchdog reset requested!", true);
#endif
            }
            else if (n == LOG_DBG_CMD_MAKETRAP)
            {
#if defined(DBG) && (OS_DEF == SMX_OS)
                int* p = (int*)1;
                *p = 0; // will trigger a trap!
#endif
            }
            else if (n == LOG_DBG_CMD_LIST_CPU)
            {
                listPMemRecord("CPU_SPD", rPMemCfgM.cpuPmemDataM.rStaticProductionDataRecordM);
                listPMemRecord("CPU_EC",  rPMemCfgM.cpuPmemDataM.rEngineeringConstantsRecordM);
                listPMemRecord("CPU_CM",  rPMemCfgM.cpuPmemDataM.rConstantsMixtureRecordM);
                listPMemRecord("CPU_RTV", rPMemCfgM.cpuPmemDataM.rRuntimeValuesRecordM);
            }
            else if (n == LOG_DBG_CMD_LIST_MIMS_SENSOR)
            {
                listPMemRecord("SENSOR_SPD", rPMemCfgM.mimsSensorPmemDataM.getSensorStaticProductionDataRecord());
                listPMemRecord("SENSOR_CPD", rPMemCfgM.mimsSensorPmemDataM.getSensorCalibratedProductionDataRecord());
            }
            else if (n == LOG_DBG_CMD_RESET_CPU)
            {
                //rPMemCfgM.cpuPmemDataM.rConstantsGeneralRecordM.resetToDefaults();
                rPMemCfgM.cpuPmemDataM.rStaticProductionDataRecordM.resetToDefaults();
                rPMemCfgM.cpuPmemDataM.rEngineeringConstantsRecordM.resetToDefaults();
                rPMemCfgM.cpuPmemDataM.rConstantsMixtureRecordM.resetToDefaults();
                rPMemCfgM.cpuPmemDataM.rRuntimeValuesRecordM.resetToDefaults();
                cout << "All cpu values reset to defaults in RAM" << endl;
            }
            else if (n == LOG_DBG_CMD_RESET_MIMS_SENSOR)
            {
                rPMemCfgM.mimsSensorPmemDataM.getSensorStaticProductionDataRecord().resetToDefaults();
                rPMemCfgM.mimsSensorPmemDataM.getSensorCalibratedProductionDataRecord().resetToDefaults();
                cout << "All MiMS sensor values reset to defaults in RAM" << endl;
            }
            else if (n == LOG_DBG_CMD_SAVE_CPU)
            {
                rPMemCfgM.cpuPmemDataM.asyncUnprotectingWriteRecordsToChip();
            }
            else if (n == LOG_DBG_CMD_SAVE_MIMS_SENSOR)
            {
                rPMemCfgM.mimsSensorPmemDataM.asyncUnprotectingWriteRecordsToChip();
            }
            else if (n == LOG_DBG_CMD_CHANGE_EE_HEX)
            {
                // "eeh" typed alone: show help
                cout << aCommandsS[n].pDescriptionStrM << endl;
                cout << "The general rule is \"eeh eename eendx newHexVal\", where \"eename\" is cpu_{cg,cm,rtv} or {ms,om,pvx}_{spd,cpd,ec,rtv}\n"
                        "\"eendx\" should be a valid field index in decimal and \"newHexValue\" is given in hexa \n"
                        "(for example if 43.2 has to be written then multiply it with 10000 for FixedPoint and transform it to hexa => 69780)" << endl;
            }
            else if (n == LOG_DBG_CMD_CHANGE_EE_DEC)
            {
                // "eed" typed alone: show help
                cout << aCommandsS[n].pDescriptionStrM << endl;
                cout << "The general rule is \"eed eename eendx newDecVal\", where \"eename\" is cpu_{cg,cm,rtv} or {ms,om,pvx}_{spd,cpd,ec,rtv}\n"
                        "\"eendx\" should be a valid field index in decimal and \"newDecValue\" is given in decimal \n"
                        "(for example if 43.2 has to be written then multiply it with 10000 for FixedPoint => 432000)" << endl;
            }
            else if (n == LOG_DBG_CMD_RESET_EE)
            {
                // "eer" typed alone: show help
                cout << aCommandsS[n].pDescriptionStrM << endl;
                cout << "The general rule is \"eer eename eendx\", where \"eename\" is cpu_{cg,cm,rtv} or {ms,om,pvx}_{spd,cpd,ec,rtv}\n"
                        "\"eendx\" should be a valid field index in decimal\n" << endl;
            }
            else if (n == LOG_DBG_CMD_SET_WARM)
            {
#ifdef MIMS_REWORK_NEEDED_SYSTEMSTARTUP
                Msf::SystemMonitor::SystemStartup::getInstance().setWarmStart(true);
                printLine("Done");
#else
                printLine("Msf::SystemMonitor::SystemStartup not implemented for MiMS yeat");
#endif
            }
            else if (n == LOG_DBG_CMD_CLEAR_WARM)
            {
#ifdef MIMS_REWORK_NEEDED_SYSTEMSTARTUP
                Msf::SystemMonitor::SystemStartup::getInstance().setWarmStart(false);
                printLine("Done");
#else
                printLine("Msf::SystemMonitor::SystemStartup not implemented for MiMS yeat");
#endif
            }
            else if (n == LOG_DBG_CMD_ENABLE_TRACE_KEY)
            {
               Msf::Log::TraceManager::getInstance().enableTracing();
               enableTrace(pCmdP);
            }
            else if (n == LOG_DBG_CMD_DISABLE_TRACE_KEY)
            {
               disableTrace(pCmdP);
            }
            else if (n == LOG_DBG_CMD_ENABLE_PROFILING)
            {
                isOutputProfileEnabled = true;
            }
            else if (n == LOG_DBG_CMD_DISABLE_PROFILING)
            {
                isOutputProfileEnabled = false;
            }
            else if (n == LOG_DBG_CMD_PRINT_ENVVARS)
            {
                rFlashBootEnvarsM.listAllVars();
            }
            else if (n == LOG_DBG_CMD_OVERFLOW_STACK)
            {
#ifdef VERIFICATION__GASMOD_SWRS_GEN_153
                //Note! The SW inside STACK_OVERFLOW_VERIFICATION #ifdef cannot be a active normally, because it may crash the SW, when the LogDebugger is used.
                printLine("Now will overflow");
                int aTheHugeArray[500]; //lint !e550 Array not used, this is just a stack overflow test.
                for (int i = 0; i < 500; ++i)
                {
                    aTheHugeArray[i] = 12;
                }
                printLine("Allocated 2Kb from stack (size 4Kb)");
                printLine("Sleeping to allow stack checker to notice.");
                int k;
                for (int i = 0; i < 600; ++i)
                {
                    k = 0;
                    while (++k < 20)
                    {
                        sleep(50);
                    }
                    printLine(".");
                }
                printLine("Still up? Test didn't work.");
#endif
            } //lint !e550 Array not used, this is just a stack overflow test.
            else if (n == LOG_DBG_CMD_OVERFLOW_HEAP)
            {
                // Repeat 4 times and wait up to 4 minutes for the system heap checker
                printLine("Allocating 400Kb from heap..");
                int* heaparray = new int[100000];
                for (int i = 0; i < 100000; ++i)
                {
                    heaparray[i] = 15;
                }
            }    //lint !e429 Memory not freed on purpose, because this tests the memory over flow.
            else if (n == LOG_DBG_CMD_LAMP_VOLTAGE_INC)
            {
                SensorVoltageControl& rSensorVoltageControl = rActuatorCfgM.getSensorVoltageControl();
                rSensorVoltageControl.setSensorVoltageTarget(rSensorVoltageControl.getSensorVoltageTarget() + 100);
            }
            else if (n == LOG_DBG_CMD_LAMP_VOLTAGE_DEC)
            {
                SensorVoltageControl& rIrLampControl = rActuatorCfgM.getSensorVoltageControl();
                rIrLampControl.setSensorVoltageTarget(rIrLampControl.getSensorVoltageTarget() - 100);
            }
            else if (n == LOG_DBG_CMD_SENSORCOMM_DIAGNOSTICS)
            {
                MimsSensorCfg::printDiagnostics();
            }
            else if (n == LOG_DBG_CMD_TEST_NORIO)
            {
                testNORIO();
            }
            else if (n == LOG_DBG_CMD_TEST_NORIO_PERF)
            {
                testNORIOPerformance();
            }
            else if (n == LOG_DBG_CMD_MEMORY_USAGE)
            {
                MemoryCfg::printMemoryUsage();
            }
            else
            {
                if ((n == LOG_DBG_CMD_READ_0_1000) || (n == LOG_DBG_CMD_READ_1_1000) ||
                   (n == LOG_DBG_CMD_WRITE_0_2000) || (n == LOG_DBG_CMD_WRITE_1_9999))
                {
                    nRepeatCntM = (n == LOG_DBG_CMD_WRITE_1_9999) ? 9999 : ((n == LOG_DBG_CMD_WRITE_0_2000) ? 2000 : 1000);
                    bRequestStoppingM = false;
                    int nPart = n % 2;
                    static Msf::Log::LogReader& rReaderS = Msf::Log::LogReader::getInstance();
                    rReaderS.clearLastReadOk(nPart);
                }
                else if ((n == LOG_DBG_CMD_READ_0_ALL) || (n == LOG_DBG_CMD_READ_1_ALL))
                {
                    nRepeatCntM = 9999; // max
                    bRequestStoppingM = false;
                    int nPart = n % 2;
                    static Msf::Log::LogReader& rReaderS = Msf::Log::LogReader::getInstance();
                    rReaderS.clearLastReadOk(nPart);
                }
                else  if ((n == LOG_DBG_CMD_ERASE_0) || (n == LOG_DBG_CMD_ERASE_1) ||
                         (n == LOG_DBG_CMD_WRITE_0) || (n == LOG_DBG_CMD_WRITE_1))
                {
                }
                else
                {
                    cout << endl << "Unknown command ??? " << dec << n << "      " << endl; //lint !e585 The sequence (???) is not a valid Trigraph sequence
                }
                Msf::RetVal rv;
                typedef Msf::Os::MemberFunctor1<LogDebugger, void, int> LogDebuggerFunctor;
                TRY_SEND_FUNCTOR(rWorkerThreadM, LogDebuggerFunctor(*this, &LogDebugger::logDebuggerFunctor, n), rv);
                MSF_ASSERT(!rv.failed());
            }
            bProcessed = true;
            break;
        }
    } // for

    if (!bProcessed)
    {
        handleSpecialCommand(pCmdP);
    }
}

void LogDebugger::logDebuggerFunctor(int n)
{
    static Msf::Log::LogReader& rReaderS = Msf::Log::LogReader::getInstance();
    switch (n)
    {
        case LOG_DBG_CMD_ERASE_0:
            rReaderS.eraseLogData(0);
            break;
        case LOG_DBG_CMD_ERASE_1:
            rReaderS.eraseLogData(1);
            break;
        case LOG_DBG_CMD_READ_0_1000:
        case LOG_DBG_CMD_READ_1_1000:
        case LOG_DBG_CMD_READ_0_ALL:
        case LOG_DBG_CMD_READ_1_ALL:
            {
                int nPart = n % 2;
                bool lastReadOk = (rReaderS.getLastReadOk(nPart) == Msf::Log::LOG_LAST_READ_NO_NEW) ? false : true;
                if (lastReadOk)
                {
                    static char aBuffS[256];
                    memset(aBuffS, 0, sizeof(aBuffS));
                    rReaderS.readNextLogData(nPart, aBuffS);
                }
                else
                {
                    nRepeatCntM = 0;
                }
            }
            break;
        case LOG_DBG_CMD_WRITE_0:
        case LOG_DBG_CMD_WRITE_1:
        case LOG_DBG_CMD_WRITE_0_2000:
        case LOG_DBG_CMD_WRITE_1_9999:
            {
                int nPart = n % 2;
                if (nPart == 0)
                {
                    MSF_LOG_INFO("a logDebuggerFunctor trace...%d", nRepeatCntM);
                }
                else
                {
                    enum
                    {
                        N = 120
                    };
                    static unsigned char IDs[N];
                    static IntU32 Vals[N];
                    for (int k = 0; k < N; ++k)
                    {
                        IDs[k] = k % 10 + '0';
                        unsigned char x1 = (k % 60 + 'A');
                        unsigned char x2 = ((k + 1) % 60 + 'A');
                        unsigned char x3 = ((k + 2) % 60 + 'A');
                        unsigned char x4 = ((k + 3) % 60 + 'A');
                        Vals[k] = (x1 << 24) + (x2 << 16) + (x3 << 8) + (x4 << 0);
                    }
                    DIAG_LOG_BINARY(Msf::Log::DIAG_HOST_COMMUNICATION, Msf::Log::DIAG_SELF_DIAGNOSTICS,
                        "__a_logDebuggerFunctor_binary_test__", IDs, Vals, N);
                }
            }
            break;
        default:
            MSF_LOG_INFO("Invalid cmd ndx %d", n);
            nRepeatCntM = 0;
            break;
    }
    if ((nRepeatCntM > 0) && !bRequestStoppingM)
    {
        if (n == LOG_DBG_CMD_WRITE_1_9999)
        {
            // for snapshots we write 4 logs at once, so don't stress the system because will fail
            // in SmxSemaphore.cpp:145 due ComponentImpl::putMsg -> semaM.release()
            sleep(400);
        }
        else if (n == LOG_DBG_CMD_WRITE_0_2000)
        {
            sleep(100);
        }
        else
        {
            sleep(10);
        }
        //cout << "(" << dec << setw(4) << setfill('0') << nRepeatCntM << ")  ";
        --nRepeatCntM;
        // send itself again
        Msf::RetVal rv;
        typedef Msf::Os::MemberFunctor1<LogDebugger, void, int> LogDebuggerFunctor;
        TRY_SEND_FUNCTOR(rWorkerThreadM, LogDebuggerFunctor(*this, &LogDebugger::logDebuggerFunctor, n), rv);
        MSF_ASSERT(!rv.failed());
    }
    else
    {
        if ((nRepeatCntM > 0) && bRequestStoppingM)
        {
            nRepeatCntM = 0;
        }
    }
}

void LogDebugger::handleSpecialCommand(const char* pCmdP) const
{
    MSF_ASSERT(NULL != pCmdP);

    // First assume eed/eeh/eer/eelist/eereset/eesave for a given PMem record.
    // If the assumption doesn't hold, nothing is done (except some parsing in vein).

    // Assume a command is at the beginning of buffM, and that the parameters follow.
    char aCmd[64] = "";
    char aParam1PMemRecName[64] = ""; // can be "cpu", "ms", "om" or "pvx" with "_spd", "_cpd", "_ec", "_rtv" or "_cg", "_cm" postfix
    const int nNrItemsScanned = sscanf(pCmdP, "%s %s", aCmd, aParam1PMemRecName);

    // Get the record to process and the chip it is stored on

    // The chip the record is stored on, if any
    Msf::MicroController::EepromChipIf* pPMemChip = NULL;

    // The record to change, if any
    /** @todo Is the const_cast really needed? It is likely a bad interface (in PMemCfg) if the const_cast is needed.
     *        This will be fixed in Rally US14771.
     */
    Msf::ParAcqToolkit::PMemRecordBuilder* pRecord = const_cast<Msf::ParAcqToolkit::PMemRecordBuilder *>(rPMemCfgM.getRecord(aParam1PMemRecName,&pPMemChip));

    // First check for eed/eeh/eer <pmem>_<record>
    const bool bHexChange  = (strcmp(aCmd, aCommandsS[LOG_DBG_CMD_CHANGE_EE_HEX].pNameStrM) == 0);
    const bool bDecChange  = (strcmp(aCmd, aCommandsS[LOG_DBG_CMD_CHANGE_EE_DEC].pNameStrM) == 0);
    const bool bFieldReset = (strcmp(aCmd, aCommandsS[LOG_DBG_CMD_RESET_EE].pNameStrM) == 0);

    if (bHexChange || bDecChange)
    {
        // "eeh" or "eed" found exactly at the beginning of buffM. Parse now buffM for all params.
        // The cmd should be like "eeh pmem_rec 4 08a49022"
        char   aDummyParam1[64] = "";
        int    nParam2Index = -1; // should be smaller than PMemRecordBuilder::getNrFields
        IntU32 nParam3Value = 0;  // new value to be set in the pmem

        if (bHexChange)
        {
            sscanf(pCmdP + strlen(aCommandsS[LOG_DBG_CMD_CHANGE_EE_HEX].pNameStrM), "%s %d %X",
                aDummyParam1, &nParam2Index, &nParam3Value);
        }
        else //if (bDecChange)
        {
            sscanf(pCmdP + strlen(aCommandsS[LOG_DBG_CMD_CHANGE_EE_DEC].pNameStrM), "%s %d %uld",
                aDummyParam1, &nParam2Index, &nParam3Value);
        }
        MSF_VERIFY(strcmp(aParam1PMemRecName,aDummyParam1)==0);

        if (pRecord && pPMemChip)
        {
            changePMemRecord(
                aParam1PMemRecName,
                *pRecord,
                nParam2Index, nParam3Value,
                *pPMemChip);
        }
        else
        {
            cout << "Unknown pmem record: " << aParam1PMemRecName << endl;
        }
    }

    else if (bFieldReset)
    {
        // "eer" found exactly at the beginning of buffM. Parse now buffM for all params.
        // The cmd should be like "eer pmem_rec 4"
        char   aDummyParam1[64] = "";
        int    nParam2Index = -1; // should be smaller than PMemRecordBuilder::getNrFields

        sscanf(pCmdP + strlen(aCommandsS[LOG_DBG_CMD_RESET_EE].pNameStrM), "%s %d",
            aDummyParam1, &nParam2Index);

        MSF_VERIFY(strcmp(aParam1PMemRecName, aDummyParam1) == 0);

        if (pRecord && pPMemChip)
        {
            pRecord->resetToDefault(nParam2Index);
            cout << aParam1PMemRecName << " field " << nParam2Index << " reset to default in RAM" << endl;
        }
        else
        {
            cout << "Unknown pmem record: " << aParam1PMemRecName << endl;
        }
    }

    // Then check for the other pmem <pmem>_<record> commands
    else if (nNrItemsScanned == 2)
    {
        if (pRecord != NULL)
        {
            if (strcmp(aCmd, aCommandsS[LOG_DBG_CMD_LIST].pNameStrM) == 0)
            {
                // eelist <pmem>_<record>
                listPMemRecord(aParam1PMemRecName, *pRecord);
            }
            else if (strcmp(aCmd, aCommandsS[LOG_DBG_CMD_RESET].pNameStrM) == 0)
            {
                // eereset <pmem>_<record>
                pRecord->resetToDefaults();
                cout << aParam1PMemRecName << " reset to defaults in RAM" << endl;
            }
            else if (strcmp(aCmd, aCommandsS[LOG_DBG_CMD_SAVE].pNameStrM) == 0)
            {
                // eesave <pmem>_<record>
                pRecord->asyncUnprotectingWriteValuesToChip();
            }
            else
            {
                // unknown command for <pmem>_<record>
                cout << "Unknown pmem command: " << aCmd << endl;
            }
        }
        else
        {
            cout << "Unknown command (or no or bad pmem record given)" << endl;
        }
    }
    else
    {
      // The command is not recognized at all
      cout << "Unknown command" << endl;
    }
}

// Keep this in sync with LogSenderHandler::listEEPROM!!! If change this then update the other too!!!
void LogDebugger::listPMemRecord(
    const char* pRecordNameP,
    const Msf::ParAcqToolkit::PMemRecordBuilder& rRecordP) const
{
    const int nNrFields        = rRecordP.getNrFields();
    const int nRecordAddress   = rRecordP.getAddress();
    const int nRecordSize      = static_cast<int>(rRecordP.getRegisteredRecordSize());
    const int nRecordTotalSize = static_cast<int>(rRecordP.getRecordSize());

    cout << "EEPROM Record: " << pRecordNameP << endl;
    cout <<
        "Address=" << dec << nRecordAddress <<
        ", fields=" << dec << nNrFields <<
        ", allocated size=" << nRecordTotalSize << "B, registered size=" << dec << nRecordSize << "B" << endl;
    cout << "index  @addr  len        (type)                                      description  value hex (        dec)  (default dec)" << endl;

    for (int i = 0; i < nNrFields; ++i)
    {
        const size_t nAddress = rRecordP.getAddress(i);
        const int nLen = rRecordP.getLen(i);
        const int nType = rRecordP.getType(i);
        const char* const pName = rRecordP.getName(i);
        void* const pData = rRecordP.getItem(i);
        const void* const pDefaultData = rRecordP.getDefaultValue(i);

        switch (nType)
        {
        case PMemRecordBuilder::PMEM_TYPE_FIXEDPOINT:
        {
            const Msf::FixedPoint* pV = static_cast<const Msf::FixedPoint*>(pData);
            const Msf::IntU32 val = pV->getInt(Msf::FixedPoint::NR_OF_DECIMALS_S);

            const Msf::FixedPoint* pDv = static_cast<const Msf::FixedPoint*>(pDefaultData);
            if (pDv)
            {
                const Msf::IntU32 dval = pDv->getInt(Msf::FixedPoint::NR_OF_DECIMALS_S);
                printf("  %03d  @%04u %4d  %12s  %47s  %08x  (%11d)  (%11d)\n", i, nAddress, nLen, "(FixPnt)", pName, val, val, dval);
            }
            else
            {
                printf("  %03d  @%04u %4d  %12s  %47s  %08x  (%11d)  ( Implicit 0)\n", i, nAddress, nLen, "(FixPnt)", pName, val, val);
            }
        }
            break;
        case PMemRecordBuilder::PMEM_TYPE_INTU32:
        {
            const IntU32* pV  = static_cast<const IntU32*>(pData);
            const IntU32* pDv = static_cast<const IntU32*>(pDefaultData);
            if (pDv)
            {
                printf("  %03d  @%04u %4d  %12s  %47s  %08x  (%11u)  (%11u)\n", i, nAddress, nLen, "(IntU32)", pName, *pV, *pV, *pDv);
            }
            else
            {
                printf("  %03d  @%04u %4d  %12s  %47s  %08x  (%11u)  ( Implicit 0)\n", i, nAddress, nLen, "(IntU32)", pName, *pV, *pV);
            }
        }
            break;
        case PMemRecordBuilder::PMEM_TYPE_INTU16:
        {
            const IntU16* pV  = static_cast<const IntU16*>(pData);
            const IntU16* pDv = static_cast<const IntU16*>(pDefaultData);
            if (pDv)
            {
                printf("  %03d  @%04u %4d  %12s  %47s      %04x  (%11u)  (%11u)\n", i, nAddress, nLen, "(IntU16)", pName, *pV, *pV, *pDv);
            }
            else
            {
                printf("  %03d  @%04u %4d  %12s  %47s      %04x  (%11u)  ( Implicit 0)\n", i, nAddress, nLen, "(IntU16)", pName, *pV, *pV);
            }
        }
            break;
        case PMemRecordBuilder::PMEM_TYPE_INTU8:
        {
            const IntU8* pV  = static_cast<const IntU8*>(pData);
            const IntU8* pDv = static_cast<const IntU8*>(pDefaultData);
            if (pDv)
            {
                printf("  %03d  @%04u %4d  %12s  %47s        %02x  (%11u)  (%11u)\n", i, nAddress, nLen, "(IntU8 )", pName, *pV, *pV, *pDv);
            }
            else
            {
                printf("  %03d  @%04u %4d  %12s  %47s        %02x  ( Implicit 0)  (%11u)\n", i, nAddress, nLen, "(IntU8 )", pName, *pV, *pV);
            }
        }
            break;
        case PMemRecordBuilder::PMEM_TYPE_STRING:
        {
            const char* pS  = static_cast<const char*>(pData);
            const char* pDs = static_cast<const char*>(pDefaultData);
            printf("  %03d  @%04u %4d  %12s  %47s  \"%s\" / \"%s\"\n", i, nAddress, nLen, "(ASCII)", pName, pS, pDs);
        }
            break;
        case PMemRecordBuilder::PMEM_TYPE_RESERVED:
            printf("  %03d  @%04u %4d  %12s  %47s\n", i, nAddress, nLen, "(Reserved)", pName);
            break;
        case PMemRecordBuilder::PMEM_TYPE_UNUSED:
            printf("  %03d  @%04u %4d  %12s  %47s  type=%d\n", i, nAddress, nLen, "UNUSED", "[Should not happen]", nType);
            break;
        default:
            printf("  %03d  @%04u %4d  %12s  %47s  type=%d\n", i, nAddress, nLen, "UNKNOWN TYPE", "[Should not happen]", nType);
            break;
        }//switch
    }//for

    // The CRC-16 is shown as an ordinary field, but it cannot be changed (even if it appears it can),
    // since its content is updated (and thus overridden) by the record class itself when the record
    // is written.

    cout << endl << endl;
}

// currently changes data by index
void LogDebugger::changePMemRecord(
    const char* pRecordNameP,
    const Msf::ParAcqToolkit::PMemRecordBuilder& rRecordP,
    int indexP,
    Msf::IntU32 nNewValP,
    Msf::MicroController::EepromChipIf& rEepromP) const
{
    MSF_ASSERT(NULL != pRecordNameP);

    const int nNrFields        = rRecordP.getNrFields();
    // Unused metadata:
    //const int nRecordAddress = rRecordP.getAddress();
    //const int nRecordSize = static_cast<int>(rRecordP.getRegisteredRecordSize());
    //const int nRecordTotalSize = static_cast<int>(rRecordP.getRecordSize());

    if (indexP >= nNrFields)
    {
        cout << endl << pRecordNameP << " EEPROM has " << dec << nNrFields << " fields! Cannot change field " << indexP << "!" << endl;
    }
    else
    {
        void* const pData = rRecordP.getItem(indexP);
        const char* const pName = rRecordP.getName(indexP);
        const int nType = rRecordP.getType(indexP);

        rEepromP.setProtection(false);

        switch (nType)
        {
        case PMemRecordBuilder::PMEM_TYPE_FIXEDPOINT:
        {
            Msf::FixedPoint* pV = static_cast<Msf::FixedPoint*>(pData);
            const Msf::IntU32 val = pV->getInt(Msf::FixedPoint::NR_OF_DECIMALS_S);
            printf("\n  %03d  %12s  %47s  %08x  (%d) changing to %08x (%d) \n", indexP, "(FixPnt)", pName, val, val, nNewValP, nNewValP);
            pV->load(static_cast<int>(nNewValP), Msf::FixedPoint::NR_OF_DECIMALS_S);
        }
            break;
        case PMemRecordBuilder::PMEM_TYPE_INTU32:
        {
            IntU32* pV = static_cast<IntU32*>(pData);
            printf("\n  %03d  %12s  %47s  %08x  (%u) changing to %08x (%u) \n", indexP, "(IntU32)", pName, *pV, *pV, nNewValP, nNewValP);
            *pV = nNewValP;
        }
            break;
        case PMemRecordBuilder::PMEM_TYPE_INTU16:
        {
            /** @par ImprovementOpportunity Add check of pName = CRC-16, and if it is,
                then print error message stating it is automatic and skip setting it
            */
            IntU16* pV = static_cast<IntU16*>(pData);
            printf("\n  %03d  %12s  %47s  %04hx  (%u) changing to %04hx (%hu) \n", indexP, "(IntU16)", pName, *pV, *pV, nNewValP, nNewValP);
            *pV = nNewValP;
        }
            break;
        case PMemRecordBuilder::PMEM_TYPE_INTU8:
        {
            IntU8* pV = static_cast<IntU8*>(pData);
            printf("\n  %03d  %12s  %47s  %02x  (%u) changing to %02x (%u) \n", indexP, "(IntU8 )", pName, *pV, *pV, nNewValP, nNewValP);
            *pV = nNewValP;
        }
            break;
        case PMemRecordBuilder::PMEM_TYPE_STRING:
        {
            /** @par ImprovementOpportunity Add support for setting strings.
             */
            const char* pS = static_cast<const char*>(pData);
            printf("\n  %03d  %12s  %47s  \"%s\". Cannot change to %08x (%d)!\n", indexP, "(string)", pName, pS, nNewValP, nNewValP);
        }
            break;
        case PMemRecordBuilder::PMEM_TYPE_RESERVED:
            printf("\n  %03d  %12s. Cannot change to %08x (%u)!\n", indexP, pName, nNewValP, nNewValP);
            break;
        case PMemRecordBuilder::PMEM_TYPE_UNUSED:
            printf("\n  %03d  %12s. Cannot change to %08x (%u)!\n", indexP, "UNUSED [Should not happen]", nNewValP, nNewValP);
            break;
        default:
            printf("\n  %03d  %12s type=%d. Cannot change to %08x (%u)!\n", indexP, "UNKNOWN TYPE [Should not happen]", nType, nNewValP, nNewValP);
            break;
        }//switch
    }

    cout << endl << endl;
}

void LogDebugger::enableTrace(const char* pCmdP)
{
    char aDomainStr[20];
    char aTraceKeyStr[20];
    char logBuff[128];
    int res = 0;

    MSF_ASSERT(NULL != pCmdP);

    res = sscanf(pCmdP, "%*s %s %s", aDomainStr, aTraceKeyStr);

    if ((0 != res) && (EOF != res))
    {
        if (Msf::Log::TraceManager::getInstance().enableTrace(aTraceKeyStr))
        {
            //Prepare the string
            sprintf(logBuff, "The key \"%s\" trace is activated", aTraceKeyStr);
            printLine(logBuff);
        }
        else
        {
            //Prepare the string
            sprintf(logBuff, "The key %s failed to activate", aTraceKeyStr);
            printLine(logBuff);
        }
        return;
    }
    printLine("Enabling the trace failed. No params found.");
}


void LogDebugger::disableTrace(const char* pCmdP)
{
    char aDomainStr[20];
    char aTraceKeyStr[20];
    char logBuff[128];
    int res = 0;

    MSF_ASSERT(NULL != pCmdP);

    res = sscanf(pCmdP, "%*s %s %s", aDomainStr, aTraceKeyStr);

    if ((0 != res) && (EOF != res))
    {
        if (Msf::Log::TraceManager::getInstance().disableTrace(aTraceKeyStr))
        {
            //Prepare the string
            sprintf(logBuff, "The key \"%s\" trace is disabled", aTraceKeyStr);
            printLine(logBuff);
        }
        else
        {
            //Prepare the string
            sprintf(logBuff, "The key %s failed to be disabled", aTraceKeyStr);
            printLine(logBuff);
        }
        return;
    }
    printLine("Enabling the trace failed. No params found.");
}

void LogDebugger::printLine(const char* pStringP)
{
    MSF_ASSERT(NULL != pStringP);
    MSF_ASSERT(NULL != pSerialPortM);

    size_t dummy;
    char buff[512];

    //Prepare the string
    sprintf(buff, "%s\n",  pStringP);
    //Send it to terminal
    pSerialPortM->write(dummy, buff, strlen(buff));
}

} // MiMS


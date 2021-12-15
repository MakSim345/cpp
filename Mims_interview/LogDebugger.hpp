#ifndef MIMS_LOG_DEBUGGER_HPP
#define MIMS_LOG_DEBUGGER_HPP 1
/**
 * Copyright (c) 2013 General Electric Company. All rights reserved.
 */
#include "Msf/Common/Os/Functors/FunctorThread.hpp"
#include "Msf/Common/Os/OsThreadAbs.hpp"
#include "Msf/Common/Primitives/MsfTypes.hpp"

// Forward Declarations
namespace Msf {
    namespace MicroController {
        class EepromChipIf;
    }//namespace MicroController
    namespace ParAcqToolkit {
        class PMemRecordBuilder;
    }//namespace ParAcqToolkit
    namespace SerialComm {
        class SerialChannelAbs;
    }//namespace SerialComm
    namespace SwToolkit {
        class OneShotAllocator;
    }//namespace SwToolkit
}//Msf

namespace MiMS {

// Forward Declarations
class PMemCfg;
class FlashBootEnv;
class ActuatorCfg;

/**
 * This singleton class is a low priority thread that polls for
 * user inputs on the serial terminal. It helps in reading the
 * logs and permanent memories, erasing them, getting the runtime, etc.
 */
class LogDebugger : public Msf::Os::OsThreadAbs
{
public:
    /** Global access to the singleton instance. */
    static LogDebugger* getInstance();

    /** Delayed start of the polling thread. */
    void startThread();
    /**
    Create the singletom instance.
    @param rWorkerThreadP [IN] the worker thread that can execute long or slow operations
    */
    static LogDebugger* createInstance(
        Msf::Os::FunctorThread& rWorkerThreadP,
        PMemCfg& rPMemCfgP,
        Msf::SerialComm::SerialChannelAbs* pSerialPortP,
        FlashBootEnv& rFlashBootEnvarsP,
        ActuatorCfg& rActuatorCfgP);

protected:
    LogDebugger(
        Msf::Os::FunctorThread& rWorkerThreadP,
        PMemCfg& rPMemCfgP,
        Msf::SerialComm::SerialChannelAbs* pSerialPortP,
        FlashBootEnv& rFlashBootEnvarsP,
        ActuatorCfg& rActuatorCfgP);
    ~LogDebugger();

    /** LogDebugger thread's endless loop routine. */
    void entry();

private:
    enum
    {
        INPUT_BUFF_SIZE = 64,

        CR_CHAR = 0x0D,   ///< CR
        LF_CHAR = 0x0A,   ///< LF
        BS_CHAR = 0x08,   ///< BACKSPACE
        SPACE_CHAR = 0x20 ///< SPACE
    };

    /** Helper for repeatetive tasks (see nRepeatCntM). */
    void logDebuggerFunctor(int n);

    /** Processes the received terminal command. */
    void handleCommand(const char* pCmdP);

    /** Processes commands taking <pmem> or <pmem>_<record> as a parameter. */
    void handleSpecialCommand(const char* pCmdP) const;

    /** Prints a header and lists each item of the given permanent memory. */
    void listPMemRecord(
        const char* pRecordNameP,
        const Msf::ParAcqToolkit::PMemRecordBuilder& rRecordP) const;

    /** Modifies the RAM value of the given permanent memory item. */
    void changePMemRecord(
        const char* pRecordNameP,
        const Msf::ParAcqToolkit::PMemRecordBuilder& rRecordP,
        int indexP,
        Msf::IntU32 nNewValP,
        Msf::MicroController::EepromChipIf& rEepromP) const;

    /** Used by command "enable tr" to enable traces. */
    void enableTrace(const char* pCmdP);

    /** Used by command "disable tr" to enable traces. */
    void disableTrace(const char* pCmdP);

    /** Used to print an entire line to terminal. */
    void printLine(const char* pStringP);

    /**
    Stores the time when the command started to be inputed.
    Used to timeout if the Enter is not detected in 25s.

    @todo This functionality seems to be completely missing from the implementation.
          Is this obsolete or what is the reason?
    @todo If not removing the code mention if the unit seconds or milliseconds.
    */
    Msf::IntU32 startTimeM;

    /** Used to repeat a specific command (see logDebuggerFunctor). */
    int nRepeatCntM;

    /** Used to stop an ongoing repetitive task. */
    bool bRequestStoppingM;

    /** Worker thread that can executed long lasting or slow operations. */
    Msf::Os::FunctorThread& rWorkerThreadM;

    /** A pointer to the singleton instance. */
    static LogDebugger* pInstanceM;

    /** Main interface to all permanent memory data. */
    PMemCfg& rPMemCfgM;

    /** Serial port used for communication. **/
    Msf::SerialComm::SerialChannelAbs* pSerialPortM;

    /** Provides access to environment variables. */
    FlashBootEnv& rFlashBootEnvarsM;

    /** Provides access to actuators like IR lamp voltage control. */
    ActuatorCfg& rActuatorCfgM;
};

} // MiMS
#endif // MIMS_LOG_DEBUGGER_HPP


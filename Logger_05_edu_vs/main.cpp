//
#include "gen.h" 
#include "div_error.h"
#include "my_exceptions.h"
#include "logger.h"
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <signal.h>


class LogInstance
{
    static boost::scoped_ptr<smart_log::Logger> m_spLogger;

public:
    static const boost::scoped_ptr<smart_log::Logger>& GetLog()
    {
        if(!m_spLogger)
        {
            smart_log::LogParameters xParams;
            xParams.m_bIsMultiThreaded = true;
            xParams.m_pErrorHandler = 0;
            xParams.m_pObfuscater = 0;
            xParams.m_siMaxSavedLogs = 0;
            xParams.m_strLogFileName = "log_file";
            xParams.m_uiLogMaxSize = 8192;
            xParams.m_xLogLevel = smart_log::eNormal;
            xParams.m_xLogSavedPath = "./log/log/log";
            m_spLogger.reset(new smart_log::Logger(xParams));
        }
        return m_spLogger;
    }
};

#define NORMAL_LOG(MSG)\
{\
    std::ostringstream xStrm;\
    xStrm << __FILE__ << ": "<< __LINE__ << " " << __FUNCTION__ << "(): " << MSG;\
    LogInstance::GetLog()->WriteNormalLog(xStrm);\
}
#define EXTENDED_LOG(MSG)\
{\
    std::ostringstream xStrm;\
    xStrm << __FILE__ << ": "<< __LINE__ << " " << __FUNCTION__ << "(): " << MSG;\
    LogInstance::GetLog()->WriteExtendedLog(xStrm);\
}
#define DEBUG_LOG(MSG)\
{\
    std::ostringstream xStrm;\
    xStrm << __FILE__ << ": "<< __LINE__ << " " << __FUNCTION__ << "(): " << MSG;\
    LogInstance::GetLog()->WriteDebugLog(xStrm);\
}

int main(int argc, char *argv[], char *envp[]) 
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 2000;

    printf ("main - start\n");
    
#define YS_23443_A
#ifdef YS_23443_A    
    __try
    {
        // my_memory_allocator();
        

    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        // memento();
    }    
#endif

    //cout << "BBeguTe 2 4ucLa gLq geLeHuq:\n";
    //cin >> num1 >> num2;
#ifdef YS_23443_B
    // App *_app = new App();
    try
    {
        // my_memory_allocator();
        // _app->Run();
        // cout << "\n$ > Press Ctr-X to exit." << std::endl;
        //float result =  quotient2(num1, num2);
        //cout << "4acTHoe paBHo: " << result << endl; 
    }
    catch (std::runtime_error _str_error)
    {
        std::cout << _str_error.what();
        throw;
    }    
    catch (...)
    {
        cout << "Unknown Error!!!!" << std::endl;
    }
#endif    
	
    //*************MAIN LOOP*****************//
    cout << "\n$ > Press Ctr-X to exit." << std::endl;

    do 
    {
        //This is simple Windows way:
        Sleep(55);
        // active_matrix->run_matrix();
       
        //nResult = produceRND();   
        //printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);
   
        //nResult = produceRND();   
        //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

        // control of endless loop (may be also in monitor.cpp)
        if (_kbhit())  // has anything been pressed from keyboard ?
        {
			NewChar=(unsigned char)_getch();
            RValue = true;            
        } 

	} while (!RValue);

	printf ("Application complete.\n");
	return 0;
}





















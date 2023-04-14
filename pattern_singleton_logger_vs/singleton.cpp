//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "singleton.h"

// Global static pointer used to ensure a single instance of the class.
OnlyOne* OnlyOne::theOnlyOneInstanceM=NULL;
Logger*  Logger::loggerInstanceM = NULL; 

Logger* Logger::getLoggerInstance()
{
    if (! loggerInstanceM)
    {
        loggerInstanceM= new Logger();
    }
    return loggerInstanceM;
}

bool Logger::openLogFile(std::string _logFile)
{
    stdOfstreamLogFileM.open(_logFile, std::ios::binary);
    return true;
}

bool Logger::closeLogFile()
{
    stdOfstreamLogFileM.close();
    return true;
}

/*
template < class T > void foo()
{
    T obj ;  // obj is dependent on template parameter
    obj.newFoo() ;  // and this works
}
*/

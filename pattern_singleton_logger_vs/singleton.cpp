//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "singleton.h"

OnlyOne* OnlyOne::theSingleInstance=NULL;

// Global static pointer used to ensure a single instance of the class.
Logger* Logger::myInstance = NULL; 

Logger* Logger::Instance()
{
    if (! myInstance)
    {
        myInstance= new Logger();
    }
    return myInstance;
}

bool Logger::openLogFile(std::string _logFile)
{
    std_ofstream_log_file.open(_logFile, std::ios::binary);
    return true;
}

bool Logger::closeLogFile()
{
    std_ofstream_log_file.close();
    return true;
}

/*
template < class T > void foo()
{
    T obj ;  // obj is dependent on template parameter
    obj.newFoo() ;  // and this works
}
*/

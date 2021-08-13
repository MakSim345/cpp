#ifndef _MY_SINGLETON_H_
#define _MY_SINGLETON_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

class Singleton
{
private:
    // static Singleton*  s_Instance;

public:
    static Singleton& Get() 
    {
        static Singleton s_Instance;
        return s_Instance;
    }
    void Hello () {}
};

class OnlyOne
{
public:
    static OnlyOne* Instance()
    {
        if(theSingleInstance == 0)
        {
            theSingleInstance = new OnlyOne;
        }
        return theSingleInstance;
    }
private:

    static OnlyOne* theSingleInstance;
    OnlyOne(){};
};

class Logger
{
public:
    static Logger* Instance();
    
    ~Logger();
    bool openLogFile(std::string logFile);
    // bool writeLogFile(std::string _str);
    bool closeLogFile();

    template <class T>   
    bool writeLogFile(T _str)
    {   
        // std::string _str = "Test" ;
        std_ofstream_log_file << _str << endl;
        return true;
    }

private:
    static Logger *myInstance;
    Logger() {};           // Private, so it cannot be called    
    Logger(Logger const&); // copy constructor
    Logger& operator=(Logger const&);
    std::ofstream std_ofstream_log_file;
};

#endif

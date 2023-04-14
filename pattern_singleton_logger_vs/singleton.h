#ifndef _SINGLETON_H_
#define _SINGLETON_H_
//============================================================
// Description:
//============================================================
#include "gen.h"

class Singleton
{
private:
    // static Singleton sInstanceM;
    Singleton() = default;

public:

    int dataM;
    
    // Explicitly prevent Copy Constructor from the usage:
    Singleton(const Singleton&) = delete;

    // Move Constructor:
    Singleton(Singleton&&) = delete; 

    // Copy Assignment operator:
    Singleton& operator=(const Singleton&) = delete;

    // Move Assignment operator:
    Singleton& operator=(Singleton&&) = delete;

    static Singleton& getSingletonInstance() 
    {
        // Note: return static, to keep it after.
        static Singleton sInstanceM;
        return sInstanceM;
    }
    void Hello () {}
};

class OnlyOne
{
public:
    static OnlyOne* getOnlyOneInstance()
    {
        if(theOnlyOneInstanceM == 0)
        {
            theOnlyOneInstanceM = new OnlyOne;
        }
        return theOnlyOneInstanceM;
    }
private:

    static OnlyOne* theOnlyOneInstanceM;
    OnlyOne(){};
};

class Logger
{
public:
    static Logger* getLoggerInstance();
    
    ~Logger() = default;
    bool openLogFile(std::string logFile);
    // bool writeLogFile(std::string _str);
    bool closeLogFile();

    template <class T>   
    bool writeLogFile(T _str)
    {   
        // std::string _str = "Test" ;
        stdOfstreamLogFileM << _str << endl;
        return true;
    }

private:
    // Private, so it cannot be called:
    Logger() {};           
    //copy constructor to prevent copy:
    Logger(Logger const&);

    Logger& operator=(Logger const&);

    static Logger* loggerInstanceM;
    std::ofstream stdOfstreamLogFileM;
};

#endif // _SINGLETON_H_
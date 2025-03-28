#pragma once
/*********************************************************************
  utils.h
**********************************************************************/
int produceRND();

int getRandomNumber();

#include "gen.h"
#include <sys/timeb.h>

class CTimer
{
public:
    CTimer();
    ~CTimer() = default;

    long Get1msTimeMS();
    void Start();
    unsigned int GetElapsedTimeMs() const;
    uint64_t GetElapsedTimeMks() const;
    // unsigned __int64 GetElapsedTimeMks() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock>  startTimeM;
    bool isTimerStarted;
    //LARGE_INTEGER m_liFreq;
    //LARGE_INTEGER m_liStart;
    //LARGE_INTEGER m_liEnd;
};


class Log
{
public:
    static const int LogLevelError   = 0;
    static const int LogLevelWarning = 1;
    static const int LogLevelInfo    = 2;

    Log():
        logLevelM(LogLevelInfo)
    {
        // mLogLebel = LogLevelInfo;
    }

private:
    int logLevelM;

public:
    void SetLevel(int pLevel)
    {
        logLevelM = pLevel;
    }

    void Warn(const char* pMessage)
    {
        if (logLevelM >= LogLevelWarning)
            std::cout << "[WARNING]:" << pMessage << "\n";
    }

    void Info(const char* pMessage)
    {
        if (logLevelM >= LogLevelInfo)
            std::cout << "[INFO]:" << pMessage << "\n";
    }

    void Error(const char* pMessage)
    {
        if (logLevelM >= LogLevelError)
            std::cout << "[ERROR]:" << pMessage << "\n";
    }
};


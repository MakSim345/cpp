#ifndef _C_TIMER_H_
#define _C_TIMER_H_
//============================================================
//
// Description:
//============================================================
#include "gen.h"

/*
class TimerClass
{
public:
    TimerClass();
    ~TimerClass();

private:
    std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
    std::chrono::duration<float> duration;
};

*/

class CTimer
{
public:
    CTimer();
    ~CTimer() = default;

    long Get1msTimeMS();
    long Get1msSinceEpoch();
    void Start();
    unsigned int GetElapsedTimeMs() const;
    uint64_t GetElapsedTimeMks() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimeM;
    bool isTimerStarted;
    unsigned long ctrTimer1MsStartM;
    unsigned long ctrTimer1MsDiffM;
};

/*
class CTimer
{
public:
    CTimer();
    ~CTimer();
    long Get1msTimeMS();
    void Start();
    unsigned int GetElapsedTimeMs() const;
    unsigned __int64 GetElapsedTimeMks() const;

private:
    LARGE_INTEGER m_liFreq;
    LARGE_INTEGER m_liStart;
    LARGE_INTEGER m_liEnd;
};
*/

#endif


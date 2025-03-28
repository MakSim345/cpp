#pragma once
/*********************************************************************

  utils.h  
  
**********************************************************************/

int produceRND();

#include <sys/timeb.h>

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

class msTimer 
{
public:
    msTimer()
    { 
        restart(); 
    }

    void restart()
    { 
        ftime(&t_start); 
    }

    float elapsedMs()
    {
        timeb t_now;
        ftime(&t_now);
        return (float)(t_now.time - t_start.time) * 1000.0f +
            (float)(t_now.millitm - t_start.millitm);
    }

private:
    timeb t_start;
};
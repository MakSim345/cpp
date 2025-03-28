#pragma once
/*********************************************************************
  utils.h
**********************************************************************/
#include "gen.h"
#include <sys/timeb.h>

int produceRND();
//void multiPlatformSleep(unsigned int milliseconds);
//void Sleep_(unsigned int milliseconds);

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


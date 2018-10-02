#ifndef _C_TIMER_H_
#define _C_TIMER_H_
//============================================================
//
//
//============================================================
//
// File:           cTimer.h
//
//============================================================
// Description:
//============================================================
#include "gen.h" 

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

#endif

#ifndef _C_TIMER_H_
#define _C_TIMER_H_
//============================================================
//
// Description:
//============================================================
#include "gen.h" 

long get_time_ms();

class CTimer
{
public:
    CTimer();
    // ~CTimer();
    //long Get1msTimeMS();
    //void Start();
    //unsigned int GetElapsedTimeMs() const;
    //unsigned __int64 GetElapsedTimeMks() const; 
    
private:
    ////LARGE_INTEGER m_liFreq;
    //LARGE_INTEGER m_liStart;
    //LARGE_INTEGER m_liEnd;
};

#endif

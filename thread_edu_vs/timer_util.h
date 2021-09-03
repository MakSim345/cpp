#pragma once
/*********************************************************************

  utils.h
  01.10.2004 Initial coding YS

**********************************************************************/
#include "gen.h"

class CTimer
{
public:
    CTimer();
	~CTimer();
    void Start();
    unsigned int GetElapsedTimeMs() const;
	unsigned __int64 GetElapsedTimeMks() const;

private:
    LARGE_INTEGER m_liFreq;
    LARGE_INTEGER m_liStart;
    LARGE_INTEGER m_liEnd;
};

// long  Get1msTime(void);
long  Get1msTimeMS(void);


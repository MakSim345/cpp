//============================================================
//
// Description:
// Tracing and debugging macros
//
// Usage:
// DEB_TRACES definition activates traces
// ASSERT and VERIFY are both compiled to debug build
// VERIFY's test assignment is compiled also to release
//
//============================================================

#ifndef __CTIMER_H__
#define __CTIMER_H__

#define WIN32_APP
#ifdef WIN32_APP
  #include <Windows.h>
#endif
		
long  Get1msTimeMS(void);

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

#endif // __CTIMER_H__

#ifndef TIMECTR_H
#define TIMECTR_H	

#include <Windows.h>

void PrintTimeN(int nCounter);
void PrintTimeMS(int nCounter);



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


#endif // TIMECTR

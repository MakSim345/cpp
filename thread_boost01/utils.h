#ifndef UTILS_H
#define UTILS_H		
/*********************************************************************

  utils.h  

**********************************************************************/
#include "stdafx.h"
#include "gen.h"
#ifdef WIN32_APP
  #include <windows.h>
#endif
		
#define CRC32_POLYNOMIAL 0xEDB88320L

long  Get1msTime(void);
long  Get1msTimeMS(void);
char* PrintTime(void); // return string with time
void PrintIntroduction();
void SendStr(char * SendString, int dest, int length);

long GetSystemCount();

// Timer class
// Constructor:
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
#endif
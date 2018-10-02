#ifndef UTILS_H
#define UTILS_H		
/*********************************************************************

  utils.h  
  01.10.2004 Initial coding YS 
  
**********************************************************************/
#include "gen.h"
  
#ifdef WIN32_APP
  #include <Windows.h>
#endif
void AddTimeStamp(int *pos,char * msg);
void AddStringPan(char * destStr, char * strToAdd,int len);
void AddShortTimeStamp(int *pos,char * msg);

int RND_Array(int);
long  Get1msTime(void);
long  Get1msTimeMS(void);
char* PrintTime(void); // return string with time
void PrintIntroduction();
void SendStr(char * SendString, int dest, int length);

int produceRND();

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

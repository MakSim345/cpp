#pragma once
/*********************************************************************

  utils.h  
  
**********************************************************************/

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

#include <sys/timeb.h>

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
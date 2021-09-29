#pragma once
/*********************************************************************

  utils.h  
  
**********************************************************************/
#include "gen.h"

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

class Log
{
public:
    static const int LogLevelError   = 0;
    static const int LogLevelWarning = 1;
    static const int LogLevelInfo    = 2;

    Log():
    mLogLebel(LogLevelInfo)
    {
        // mLogLebel = LogLevelInfo;
    }

private:
    int mLogLebel;

public:
    void SetLevel(int pLevel)
    {
        mLogLebel = pLevel;
    }

    void Warn(const char* pMessage)
    {   
        if (mLogLebel >= LogLevelWarning)
            std::cout << "[WARNING]:" << pMessage << "\n";
    }

    void Info(const char* pMessage)
    {
        if (mLogLebel >= LogLevelInfo)
            std::cout << "[INFO]:" << pMessage << "\n";
    }

    void Error(const char* pMessage)
    {
        if (mLogLebel >= LogLevelError)
            std::cout << "[ERROR]:" << pMessage << "\n";
    }
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

class Programmers
{
public:
    Programmers()
    {

    }

    Programmers(int iWeightP, int iAgeP)
    {
        this->weight = iWeightP;
        this->age = iAgeP;
    }

    // simply get references to value created in main and change them    
    void getParams(int &getWeightP, int &getAgeP)
    {
        getWeightP=weight;
        getAgeP=age;
    }

private:
    int weight;
    int age;
};
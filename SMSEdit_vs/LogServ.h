#ifndef LOGSERV_H
#define LOGSERV_H
/*********************************************************************

  01.10.2004 Initial coding YS

**********************************************************************/

#ifdef WIN32_APP
  #include <Windows.h>
#endif

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

long  Get1msTimeMS(void);

class CTRACE
{
public:
    CTRACE();
    CTRACE(int, int);
    CTRACE(int, int, char*);
   ~CTRACE();
    void TRACEY(char*, int);
    void TRACEY(char*, int, int);
    void TRACEY(char*, int, int, int);
    void TRACEY(char*, int, int, int, int);
    void TRACEY(char*, long);
    void TRACEY(char*, double);
    void TRACEY(char*, char*);
    void TRACEY(char*, char*, int);
    void TRACEY(char*);
    void TRACEY(char);
    void TIMESTAMP();
    void TIMESTAMP(int);
    void TRACE_HEX(char*, int);

private:
    void TRACE_Init();
    char *m_FileNameF;// = "allegro.log";
    FILE *fi;// = NULL;
    int m_FileIsOpen;
    int m_TraceToFile;
    int m_TraceToCons;

};


#endif // LOGSERV_H

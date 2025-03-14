#ifndef _TIMER_H_
#define _TIMER_H_
/*********************************************************************

  timer.h
  01.10.2004 Initial coding YS

**********************************************************************/
#include "gen.h"

long  Get1msTime(void);
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

//====================================================================
#include <sys/timeb.h>
class msTimer
{
public:
    msTimer() { restart(); }
    void restart() { ftime(&t_start);}

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

/* Example of usage:
 *
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    msTimer t;
    for (int i = 0; i < 5000000; i++)
        ;
    std::cout << t.elapsedMs() << endl;
    return 0;
}
*
* */

#endif

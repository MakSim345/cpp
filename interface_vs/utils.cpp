#include "utils.h"

extern long g_lTimeTick;

int produceRND()
{
    static int nFirstTime = 1;
    int random;

    if (1 == nFirstTime)
    {
        srand ((unsigned)time (NULL));
        nFirstTime = 0;
    }
    random = 1 + (rand() % RND_MAX);
    return random;
}

CTimer::CTimer() :
    isTimerStarted(false)
    {
        this->Start();
    }

long CTimer::Get1msTimeMS()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
}

void CTimer::Start()
{
    startTimeM = std::chrono::high_resolution_clock::now();
    isTimerStarted = true;
}

unsigned int CTimer::GetElapsedTimeMs() const
{
    // Returns the elapsed time in number of milliseconds
    //if (!isTimerStarted)
    //{
    //    return 0;
    //}
    auto endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (endTime - startTimeM).count();
}

uint64_t CTimer::GetElapsedTimeMks() const
{
    // Returns the elapsed time in number of microseconds
    auto endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>
        (endTime - startTimeM).count();
}

/*
 * Note: Follow works only for Win32! Not cross-platformed.
CTimer::CTimer()
{
    ::QueryPerformanceFrequency(&m_liFreq);
    Start();
    // printf ("QueryPerformanceFrequency : %u\n", m_liFreq.QuadPart);
}

void CTimer::Start()
{
 ::QueryPerformanceCounter(&m_liStart);
}

unsigned int CTimer::GetElapsedTimeMs() const
{
  LARGE_INTEGER liEnd;
  ::QueryPerformanceCounter(&liEnd);
  return static_cast<unsigned int>((liEnd.QuadPart - m_liStart.QuadPart) * 1000 / m_liFreq.QuadPart);
}

unsigned __int64 CTimer::GetElapsedTimeMks() const
{
  LARGE_INTEGER liEnd;
  ::QueryPerformanceCounter(&liEnd);
  return static_cast<unsigned __int64>((liEnd.QuadPart - m_liStart.QuadPart) * 1000000 / m_liFreq.QuadPart);
}
*/

/********************************************************************

  Declaration: implementation of Get1msTime() for Microsoft env.
  Call: Get1msTimeMS(void)
  Input: none
  Returns: milliseconds.

*********************************************************************/
long  Get1msTimeMS(void)
{
  /*
  // 1. Use function  _ftime
   struct _timeb timebuffer;

  _ftime( &timebuffer );
  // g_lTimeTick = (timebuffer.time*1000)+timebuffer.millitm;
  return (timebuffer.time*1000)+timebuffer.millitm;
  */

  /*
  // 2. Use function GetTickCount():
  // after 49 days it will reset. Check it!
  return GetTickCount();
  */

  /*
   // 3. Use  QueryPerformanceCounter () function:
  __int64 nTick, f;

  // This function must be called once!
  QueryPerformanceFrequency((PLARGE_INTEGER)&f);

  QueryPerformanceCounter((PLARGE_INTEGER)&nTick);
  // printf ("Freq : %u\n",f);
  // printf ("nTick: %u, nTick/f:%u\n",nTick, nTick/f);
  return (long)(nTick/3000000); // divide to processor speed!!!
  */

   // 3. Use class based on QueryPerformanceCounter () functions:
   //static int nFirsTime = 1;
   static CTimer *t = new CTimer(); // take memory from heap, not from stack!

/*
   if (1 == nFirsTime)
    {
      t.Start();
      nFirsTime = 0;
    }
 */
   return t->GetElapsedTimeMs();
   //return t.GetElapsedTimeMks();
}

void PrintIntroduction()
{
  int i;
  int nFrame = 59;
  printf ("\t%c", 201);
  for (i=0; i<nFrame; i++)
    printf ("%c", 205);

    printf ("%c\n", 187);
    printf ("\t%c The wait command is used within a computer batch file     %c\n", 186, 186);
    printf ("\t%c and allows the computer to pause the currently running    %c\n", 186, 186);
    printf ("\t%c batch file for an amount of milliseconds .                %c\n", 186, 186);
    printf ("\t%c Usage: 'WAIT 1000' will wait for 1 second.                %c\n", 186, 186);
    printf ("\t%c                                                           %c\n", 186, 186);
    printf ("\t%c                   GE (c) 2007.                            %c\n", 186, 186);

    printf ("\t%c", 200);

    for (i=0; i<nFrame; i++)
    {
       printf ("%c", 205);
    }

    printf ("%c\n", 188);
};


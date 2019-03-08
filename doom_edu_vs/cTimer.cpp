//============================================================
//
// Description:
// Timer class
//============================================================
#include "cTimer.h"

// Constructor:
CTimer::CTimer()
{
 ::QueryPerformanceFrequency(&m_liFreq);
 Start();
 // printf ("QueryPerformanceFrequency : %u\n", m_liFreq.QuadPart);
}

/********************************************************************

  Declaration:
  Call:
  Input:
  Returns:

*********************************************************************/
void CTimer::Start()
{
 ::QueryPerformanceCounter(&m_liStart);
}

/********************************************************************

  Declaration:
  Call:
  Input:
  Returns:

*********************************************************************/
unsigned int CTimer::GetElapsedTimeMs() const
{
  LARGE_INTEGER liEnd;
  ::QueryPerformanceCounter(&liEnd);
  return static_cast<unsigned int>((liEnd.QuadPart - m_liStart.QuadPart) * 1000 / m_liFreq.QuadPart);
}

/********************************************************************

  Declaration:
  Call:
  Input:
  Returns:

*********************************************************************/
unsigned __int64 CTimer::GetElapsedTimeMks() const
{
  LARGE_INTEGER liEnd;
  ::QueryPerformanceCounter(&liEnd);
  return static_cast<unsigned __int64>((liEnd.QuadPart - m_liStart.QuadPart) * 1000000 / m_liFreq.QuadPart);
}

long CTimer::Get1msTimeMS(void)
{
    return GetElapsedTimeMs();
}
// End of the class.

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
   //return t.GetElapsedTimeMs();
   //return t.GetElapsedTimeMks();
}

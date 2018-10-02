#pragma once

#include "gen.h"
#include "utils.h"
#include "timectr.h"
#include <stdlib.h>


#include <Windows.h>

// Timer class
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
    
/*   if (1 == nFirsTime)
	{
      t.Start();
	  nFirsTime = 0;
	}
 */
   return t->GetElapsedTimeMs();
   //return t.GetElapsedTimeMs();
   //return t.GetElapsedTimeMks();

}

/********************************************************************

  Declaration: 
  Call: 
  Input:
  Returns:
  01.09.2006 Initial coding

*********************************************************************/
void PrintTimeN(int nCounter)
{

// printf ("PENTIUM time: %d, Counter %d\n", Get1msTime(), nCounter);
static int n_days   = 0;
static int n_hours   = 0;
static int n_minutes = 0;
static int n_seconds = 0;
static int n_millisc = 0;
static int n_milctr  = 0;
static int nBuff     = 0; 
static int nResult   = 0; 
static int nFirstTime= 1;
 
if (nFirstTime == 1)
{
 nFirstTime = 0;
 nBuff = nCounter; 
}

 nResult = nCounter - nBuff;
 nBuff = nCounter; 
 n_millisc = n_millisc + nResult;
 
 if (n_millisc >= 100)
 {  
  n_milctr++;
  n_millisc= 0;
  if (n_milctr >= 10)
  {   
   n_milctr = 0;
   n_seconds++;
   if (n_seconds >= 60)
   {
    n_seconds = 0;
    n_minutes++;
	if (n_minutes >= 60)
	{
     n_minutes = 0;
     n_hours++;
	 if (n_hours >= 24)
	 {      
      n_hours = 0;
	  n_days++;
     }
    }	 
   }
  }   
  // _dos (cls);
   // system("cls");
   //printf ("\n\n\n\n\n\n\n\t\t");
   printf ("TIME: %02d D %02d H %02d M %02d S %03d MS ", n_days, n_hours, n_minutes, n_seconds, n_milctr*100);  
 }
 
}

/********************************************************************

  Declaration: 
  Call: 
  Input:
  Returns:
  01.09.2006 Initial coding

*********************************************************************/
void PrintTimeMS(int nCounter)
{

// printf ("PENTIUM time: %d, Counter %d\n", Get1msTime(), nCounter);
static int n_days   = 0;
static int n_hours   = 0;
static int n_minutes = 0;
static int n_seconds = 0;
static int n_millisc = 0;
static int n_milctr  = 0;
static int nBuff     = 0; 
static int nResult   = 0; 
static int nFirstTime= 1;
 
if (nFirstTime == 1)
{
 nFirstTime = 0;
 nBuff = nCounter; 
}
	
 nResult = nCounter - nBuff;
 nBuff = nCounter; 
 n_millisc = n_millisc + nResult;
 
 if (n_millisc >= 100)
 {  
  n_milctr++;
  n_millisc= 0;
  if (n_milctr >= 10)
  {   
   n_milctr = 0;
   n_seconds++;
   if (n_seconds >= 60)
   {
    n_seconds = 0;
    n_minutes++;
	if (n_minutes >= 60)
	{
     n_minutes = 0;
     n_hours++;
	 if (n_hours >= 24)
	 {      
      n_hours = 0;
	  n_days++;
     }
    }	 
   }
  }   
  // _dos (cls);
   //system("cls");
   //printf ("\n\n\n\n\n\n\n\t\t");
   printf ("MSTM: %02d days %02d hrs %02d min %02d sec %03d ms ", n_days, n_hours, n_minutes, n_seconds, n_milctr*100);  
 }
 
}
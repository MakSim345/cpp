
#include "stdafx.h"

#include <time.h>
#include "stdio.h"
#include "utils.h"

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

// long g_lTimeTick;

/*-----------------------------------------------------------------------

 Get 1 ms Time Count from midnight

  -----------------------------------------------------------------------*/

// this also works but gives some warning when compiling
//long long rdtsc(void)
//{
//__asm__("rdtsc");
//}

/*
inline long long rdtsc (void)
{
        long long result;
        asm volatile ("rdtsc" : "=A"(result));
        return result;
}
*/
/**********************************************
From Wikipedia, the free encyclopedia
In the X86 assembly language, the RDTSC instruction is a mnemonic for 
Read Time Stamp Counter. The instruction returns a 64 bit value in 
registers EDX:EAX the count of ticks from processor reset. 
Added in Pentium. Opcode: 0F 31.
Examples of using it in Microsoft Visual C++:
************************************************/
__declspec(naked)
unsigned __int64 __cdecl rdtsc(void)
{
   __asm
   {
      rdtsc
      ret       ; return value at EDX:EAX
   }
}

/********************************************************************

  Declaration:  Get 1 ms Time Count from midnight
  Call: Get1msTime(void)
  Input: none
  Returns: milliseconds.
  	  
*********************************************************************/ 

long  Get1msTime(void)
  {
#if defined PENTIUM   
   unsigned __int64  tsc;
   tsc=rdtsc();      
   return( (long)(tsc/(MHz*1000)));
#else
  // not pentium
  return g_lTimeTick;
#endif
  }

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
  Call: GetSystemCount()
  Input: None
  Returns: System count
  12.10.2006 Initial coding

*********************************************************************/

long GetSystemCount()
  {		
	// return (long)(_farpeekw(0x0040,0x006C) + _farpeekw(0x0040,0x006E)*65536l);
	return (long) GetTickCount();  
  }


/*-----------------------------------------------------------------------

Returns Time/Date String

  -----------------------------------------------------------------------*/  
/*
char* PrintTime(void) 
	{

 	char ReturnTime[100];
 	struct date d;
	struct time t;
 
 	getdate(&d);
	gettime(&t);
  
  sprintf(ReturnTime,"%02d/%02d/%02d %02d:%02d:%02d", 
           d.da_day,d.da_mon,d.da_year,
           t.ti_hour,t.ti_min,t.ti_sec);  // timestamp

  return ReturnTime;
}
*/ 	
void PrintIntroduction()
{
  int i;
  int nFrame = 59;
	printf ("\t%c", 201);
	for (i=0; i<nFrame; i++)
	   printf ("%c", 205);
    printf ("%c\n", 187);	
	printf ("\t%c Application printing out every 1 seconds the              %c\n", 186, 186);
	printf ("\t%c number of PPS signals in TestPPS value.                   %c\n", 186, 186);
	printf ("\t%c The TestPPS has to grow by 1 every second.                %c\n", 186, 186);
	printf ("\t%c Type 'Ctrl-X' for end.                                    %c\n", 186, 186);
	
	printf ("\t%c", 200);
	for (i=0; i<nFrame; i++)
	   printf ("%c", 205);
	printf ("%c\n", 188);	
  //printf ("\n");


};

/********************************************************************

  Declaration: Output string to the latest origin
  Call: SendStr(string,dest)
  Input:  char * string, int destination (0 only display)
  Returns:
  27.11.2000 Initial coding

*********************************************************************/

void SendStr(char * SendString,int dest,int length)
{
  //int Port;
int j;

for (j=0;j<length;j++)
{
  if (dest)
  {
   //printf("%c",SendString[j]);
  }
  else
  {
   printf("%c",*(SendString+j));
  }
 }
 
} 

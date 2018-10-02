#include "gen.h" 
//#include <time.h>

#include "utils.h"
// #include "stdafx.h"

extern long g_lTimeTick;

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
/*-----------------------------------------------------------------------  
  Call: ret=CalcCS(transmit,string,nbrofchars,recvCS)
  Input: int               transmit (1 = transmit, 0=receive)
         unsigned char * string     target string
         int nbrofchars    how many chars are there to be calculated
         unsigned char recvCS       received CS (if transmit = 0)
  Returns: unsigned char ret (if transmit=1 -> CS,  if transmit=0 -> 0 (error)
                     or 1 (CS OK)
  Original Coding: 

  -----------------------------------------------------------------------
*/

unsigned char CalcCS(int transmit, unsigned char * string, int nbrofchars, unsigned char recvCS)
{
  int i;
  unsigned char CRC=0;

  //  calculate CS
  for (i=0; i < nbrofchars; i++)
    {
     CRC = CRC ^ string[i];
    }

  if (transmit)
     return(CRC);
  else
   {
    if (CRC == recvCS)
       return(1);
    else
     {    
#if defined DEBUG
      int j;
      printf("CRC Error: %x %x *",CRC,recvCS);
      for (j=0; j<nbrofchars; j++)
         printf("/%d",string[j]);
#endif
      return(0);
     }
   }    
}



/*
Calculates a CRC value to be used by CRC calculation functions.
*/
unsigned long CRC32Value(int i)
{
  int j;
  unsigned long ulCRC;

  ulCRC = i;
  for(j=8;j>0;j--)
  {
    if(ulCRC & 1)
      ulCRC = (ulCRC>>1)^CRC32_POLYNOMIAL;
    else
      ulCRC>>=1;
  }

  return ulCRC;
}

/*
Calculates the CRC-32 of a block of data all at once
ulCount: Number of bytes in the data block
ucBuffer: Data block
*/
unsigned long CalculateBlockCRC32(
                                  unsigned long ulCount,
                                  unsigned char* ucBuffer)
{
  unsigned long ulTemp1;
  unsigned long ulTemp2;
  unsigned long ulCRC = 0;

  while( ulCount-- != 0 )
  {
    ulTemp1 = ( ulCRC>>8 ) & 0x00FFFFFFL;
    ulTemp2 = CRC32Value( ((int)ulCRC ^ *ucBuffer++) & 0xFF );
    ulCRC = ulTemp1 ^ ulTemp2;
  }

  return ulCRC;
}


//*********************************************************************
void AddShortTimeStamp(int *pos,char * msg)

//      Concanates timestamp for IPA TOS, in format:
//      HHMMSS
{
    char datetime[6];
/*    struct time t;    
    
    gettime(&t);
    sprintf(datetime, "%02d%02d%02d",
             t.ti_hour, t.ti_min, t.ti_sec);
*/
   for (int i=0; i<6; i++)
     {
     *msg=datetime[i];
     msg++;
     }

   *pos=*pos+6;
}    
    
//*********************************************************************
void AddTimeStamp(int *pos,char * msg)

//      Concanates timestamp for SPARCS Movement msg.Timestamp format:
//      YYYYMMDDHHmmSS
{
    char datetime[14];
    /*
    struct time_t t;
    struct date_d d;

    getdate(&d);
    gettime(&t);
    sprintf(datetime,"%d%02d%02d%02d%02d%02d",
            d.da_year,d.da_mon,d.da_day,
            t.ti_hour,t.ti_min,t.ti_sec);
  */
   for (int i=0; i<14; i++)
     {
     *msg=datetime[i];
     msg++;
     }
   *pos=*pos+14;
   
}    
/*
int rand()
{
  // from K&R - produces a random number between 0 and 32767.
 int rand_seed = RND_MAX;
 
    rand_seed = rand_seed * 1103515245 +12345;
    return (unsigned int)(rand_seed / 65536) % 32768;
}
*/

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
    printf ("\t%c This is a time difference utility for batch files.        %c\n", 186, 186);
    printf ("\t%c Usage: no arguments needed. First run will remember the   %c\n", 186, 186);    
    printf ("\t%c current time. Second run will show you how long time      %c\n", 186, 186);    
    printf ("\t%c passed since first run.                                   %c\n", 186, 186);    
  printf ("\t%c                                                           %c\n", 186, 186);
  printf ("\t%c                   GE (c) 2007.                            %c\n", 186, 186);

    printf ("\t%c", 200);
    for (i=0; i<nFrame; i++)
       printf ("%c", 205);
    printf ("%c\n", 188);    
  //printf ("\n");
}

#ifdef WAIT_APPLICATION
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
       printf ("%c", 205);
    printf ("%c\n", 188);    
  //printf ("\n");
}
#endif //WAIT_APPLICATION

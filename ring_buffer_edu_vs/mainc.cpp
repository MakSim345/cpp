// dev001.cpp : Defines the entry point for the console application.
//

#include "gen.h"
#include "utils.h"
#include "timectr.h"
#include "RingBuffer.h"

#define STRICT 1
#include <windows.h>
//#include <Mmsystem.h>
#include <iostream>
#include <stdio.h>

#include <sys/timeb.h>
#include <time.h>
#include <math.h>

long g_lTimeTick = 0;

int NewChar=0;

VOID CALLBACK interrupt_set(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
    static long g_lTime = 0;
    printf ("Time: %ld, diff = %d\n", dwTime, dwTime - g_lTime );
    g_lTimeTick += TIME_TICK_INTERVAL;
    g_lTime = dwTime;
}


float quotient (int num1, int num2)
{
    if (num2 == 0)
        throw DivideByZeroError();

    return (float) num1/num2;
}

int main(int argc, char *argv[], char *envp[])
{
    unsigned long LastTimeIn=0;
    long LastTimeInMS = 0;
    int RValue = false;
    int Counter=0;
    int nSec=0;
    int nOpenFileToken = 0;
    unsigned int *nLen;
    double nTest;
    char *FileNameF = "TimeSt.log";
    FILE *fi = NULL;

    int RingBuffSize= 10;


    Ring_Buffer RNGBUF(RingBuffSize);

    // RNGBUF = new Ring_Buffer(buff, 100);

    //printf ("RNGBUF.Free_Space = %d\n", RNGBUF.Free_Space());

 // open the file for input:
 if ( (fi = fopen(FileNameF, "a+") ) != NULL)
  {
  // printf ("file %s was open succesfully\n", FileNameF);
   nOpenFileToken = 1;
  }
 else
  {
   printf ("file %s was not open\n", FileNameF);
   getchar(); 
   nOpenFileToken = 0;
  }

  fprintf(fi, "Start time: %d\n", Get1msTime());
  //*********************TEST MODULE**************

    //printf ("BEFORE time: %ld\n", Get1msTimeMS());
     // printf( "\n");
    //for (int i=1; i<100; i++)
    //   nTest = sqrt(890);
    // Sleep(20);
    //printf ("AFTER time: %ld\n", Get1msTimeMS());
    //return 0;

  //**********************************************

   // nSec = 65;
//*************MAIN LOOP*****************//
 do
 {
    ++Counter;

   if ((( Get1msTimeMS() - LastTimeInMS)>100-1) || (LastTimeInMS > Get1msTimeMS() ))
    {
     PrintTimeMS(Get1msTimeMS());
     printf( "\n");
     //printf ("NO-PENT time: %ld\n", Get1msTimeMS());
     LastTimeInMS = Get1msTimeMS();
    
    //printf ("%d sec. - PENTIUM time: %d, Counter %d\n", nSec, Get1msTime(), Counter);
    //printf ("PENTIUM time: %d\n", Get1msTime());
    //printf ("NO-PENT time: %d, Counter %d\n", Get1msTime2(), Counter);
    //PrintTimeMS(Get1msTimeMS());
    //printf( " -- ");
    //PrintTimeN(Get1msTime());
    //printf( "\n");

    //printf ("PENTIUM time: %d, Pa3HocTb: %d\n",Get1msTime(), Get1msTime() - LastTimeIn);
    //printf ("NO-PENT time: %u, Pa3HocTb: %d\n", Get1msTimeMS(), (Get1msTimeMS() - LastTimeInMS));
    //printf ("NO-PENT time: %u, Pa3HocTb: %d\n", t.GetElapsedTimeMks(), (t.GetElapsedTimeMks() - LastTimeInMS));
    LastTimeIn = Get1msTime();
    // LastTimeInMS = Get1msTimeMS();
    //LastTimeInMS = t.GetElapsedTimeMks();
    RNGBUF.PrintDump();
    RNGBUF.Put_Data(nSec);
    //printf ("RNGBUF.GetData = %c\n", RNGBUF.Get_Data());
    ++nSec;
    //RND_Array(1);
    }

    // control of endless loop (may be also in monitor.cpp)
    if (kbhit())  // has anything been pressed from keyboard ?
    {
       NewChar=(unsigned char)getch();
     if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
     {
      RValue = true; // END mark
     }
    }

}while (!RValue);

 if (1 == nOpenFileToken)
   fclose (fi);

 printf ("Application complete.\n");

return 0;
}


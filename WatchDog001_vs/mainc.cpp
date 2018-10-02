#include "gen.h"
#include "monitor.h"
#include "utils.h"
#include "timectr.h"
#include "commport.h"
#include "comminc.h"
#include "RingBuffer.h"
#include "NetworkServices.h"
#include "ITLCD.H"

#include <windows.h>
#include <stdio.h>

#include <sys/timeb.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "TCHAR.h"

 long g_lTimeTick = 0;
 int DispSync=0;
 int MainNewChar=0;
 CommPort *CPort[NBR_OF_PORTS];
 CTRACE t(1,1);

int main(int argc, char *argv[], char *envp[]) 
{
	long LastTimeIn=0;	
	long LastTimeInMS = 0;	
	int RValue = false;
	int Counter=0;	
	int nSec=0;
	int nOpenFileToken = 0;
  unsigned long uResult = 0;
	  
	typedef DWORD (*pOpenItlcd)(VOID);
	typedef DWORD (*pCloseItlcd)(VOID);
	typedef DWORD (*pReadMonitor)(HWMON *Mon);

	typedef DWORD (*pEnableWD)(VOID);
	typedef DWORD (*pSetWDTimer)(UCHAR Time);
	
	HINSTANCE ItlcdLib; 
	
  pOpenItlcd OpenItlcd;
	pCloseItlcd CloseItlcd;
	pReadMonitor ReadMonitor;
  
	pEnableWD EnableWD;
  pSetWDTimer SetWDTimer;

	
	HWMON sHWMON = {0};

	CHAR Text[100] = {0};

	printf ("Time: %ld. Before read library\n",Get1msTimeMS());

	// Open library ITLCD.LIB:
	if ((ItlcdLib = LoadLibrary("itlcd.dll")) != NULL)
	{
		printf ("Time: %ld. LoadLibrary('itlcd.dll') returns: 0x%X\n",Get1msTimeMS(), ItlcdLib);

		if((OpenItlcd = (pOpenItlcd) GetProcAddress( ItlcdLib, "OpenItlcd" )) != NULL)
		{	
		 printf ("Time: %ld. GetProcAddress(ItlcdLib, 'OpenItlcd') returns: 0x%X\n", Get1msTimeMS(), OpenItlcd);
		 
		 if(OpenItlcd())
			{
				printf ("Driver Open - OK\n");
			}
		else
		{
			// MessageBox(NULL,"Driver Open","FAIL",0);
			printf ("Driver Open - FAIL\n");
		}
		}
	}

	else
	{
	 // MessageBox(NULL,"Unable to open LoadLibrary Itlcd.dll","FAIL",0);  
	  printf ("Unable to open LoadLibrary Itlcd.dll\n");
		return 0;
	}

// #define USE_OUTPUT_FILE  
#ifdef USE_OUTPUT_FILE	
	char *FileNameF = "allegro.log";
	FILE *fi = NULL; 
  
// open the file for input:	
 if ( (fi = fopen(FileNameF, "w") ) != NULL)
  {
  // printf ("file %s was open succesfully\n", FileNameF);
   nOpenFileToken = 1;
  }
 else
  {
   printf ("file %s was not open\n", FileNameF);
   getchar(); // nay3a, xyLe...
   nOpenFileToken = 0;
  }
	  
  fprintf(fi, "Start time: %d\n", Get1msTimeMS());
#endif  //USE_OUTPUT_FILE

//*********************TEST MODULE**************
/*
  for (int j=0; j <sizeof(TstDouble); j++)
	{
	 t.TRACE("[%d]=",j);		
	 t.TRACE("[0x%X]\n", TstArr[j]);
	}
	t.TRACE("\n");
	// memcpy((void *)&TstDouble, (const void*)&TstArr, 8);	
   return 0;
*/
	//*************MAIN LOOP*****************//
 
 unsigned long ReadMonitorResult;
 /*
 t.TRACE("Time: %ld Before SetWDTimer()\n",Get1msTimeMS() );
 ReadMonitorResult = SetWDTimer(0x2A);
 t.TRACE("SetWDTimer return: %d ()\n", (int)ReadMonitorResult);
  
 t.TRACE("Time: %ld Before EnableWD()\n",Get1msTimeMS() );
 
 	ReadMonitorResult = EnableWD();
 t.TRACE("EnableWD return: %d ()\n", (int)ReadMonitorResult);
 */

 /*
 t.TRACE("Time: %ld Before SetWDTimer()\n",Get1msTimeMS() );
 if((SetWDTimer = (pSetWDTimer) GetProcAddress( ItlcdLib, "SetWDTimer" )) != NULL)
 { 	
 	ReadMonitorResult = SetWDTimer(0x2A);
	t.TRACE("SetWDTimer return: %d ()\n", (int)ReadMonitorResult);
 } 
 
 t.TRACE("Time: %ld Before EnableWD()\n",Get1msTimeMS() );
 
 if((EnableWD = (pEnableWD) GetProcAddress( ItlcdLib, "pEnableWD" )) != NULL)
 {
 	ReadMonitorResult = EnableWD();
 } 	
 
 t.TRACE("EnableWD return: %d ()\n", (int)ReadMonitorResult);
 t.TRACE("Time: %ld After EnableWD()\n", Get1msTimeMS() );
*/
 printf ("Main LOOP entrance. Time: %ld\n", Get1msTimeMS()); 

 do 
 {    
	++Counter;    
   
 if ((( Get1msTimeMS() - LastTimeInMS)>1000-1) || (LastTimeInMS > Get1msTimeMS() ))
	{ 
	 	// Call ReadMonitor proc form library ITLCD.LIB:
	 if((ReadMonitor = (pReadMonitor) GetProcAddress( ItlcdLib, "ReadMonitor" )) != NULL)
	 {
		// printf ("Time: %ld. Before ReadMonitor()\n",Get1msTimeMS());
		// if(ReadMonitor(&sHWMON))
		ReadMonitorResult = ReadMonitor(&sHWMON);
		// printf ("Time: %ld. After ReadMonitor()\n",Get1msTimeMS());
		if (ReadMonitorResult)
		{
		 // sprintf(Text,"Core Voltage %1.3f",sHWMON.VCORE);
		 // printf("Core Voltage - %1.3f",sHWMON.VCORE);
		 printf ("Time: %ld. Core Voltage - %1.3f\n",Get1msTimeMS(), sHWMON.VCORE);
		 printf ("Time: %ld. Core CPUTemp - %1.3f\n\n",Get1msTimeMS(), sHWMON.CPUTemp);
		 // MessageBox(NULL,Text,"OK",0);
	  }
	  else
	  {
	 	 //MessageBox(NULL,"ReadMonitor function","FAIL",0);	
		 printf ("ReadMonitor function - FAIL\n");
	  }
	 }	  
		LastTimeInMS = Get1msTimeMS();
	
  }   
	
	// control of endless loop (may be also in monitor.cpp)
	// RValue=monitor(DispSync);

if (kbhit())  // has anything been pressed from keyboard ?
	{       
   MainNewChar=(unsigned char)getch();
	 if ((MainNewChar & 0xff) == 24)  // CTRL-X   pressed
	 {
	  RValue = true; // END mark
	 }     
	}

 } while (!RValue);  


 // Close library ITLCD.LIB:
	if((CloseItlcd = (pCloseItlcd) GetProcAddress( ItlcdLib, "CloseItlcd" )) != NULL)
	{
	  if(CloseItlcd())
		{
	   // MessageBox(NULL,"Driver Close","OK",0);
			printf ("Driver Close - OK\n");
		}
	  else
		{
		 // MessageBox(NULL,"Driver Close","FAIL",0);
		 printf ("Driver Close - FAIL\n");
		}
	 }	
	 FreeLibrary(ItlcdLib);

#ifdef USE_OUTPUT_FILE	
 fprintf(fi, "End time: %d\n", Get1msTimeMS());
 if (1 == nOpenFileToken)
   fclose (fi);
#endif

 printf ("\nApplication complete.\n");

return 0;
}


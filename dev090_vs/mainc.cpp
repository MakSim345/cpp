// edu05.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gen.h"
// #include "trace.h"
// #include "utils.h"
#include "commport.h"
#include "RingBuffer.h"
#include  <math.h>

#include "ctimer.h" 
#include <iostream>

#define STRICT 1 
//#include <windows.h>
//#include <Mmsystem.h>
//#include <iostream.h>
//#include <stdio.h>

#include <sys/timeb.h>

//#include <math.h>
//#include <assert.h>

#include "TCHAR.h"

long g_lTimeTick = 0;

int NewChar=0;

using namespace std;

// Trace *t;

/*
std::string format(const char *fmt, ...) 
{ 
   using std::string;
   using std::vector;

   string retStr("");

   if (NULL != fmt)
   {
      va_list marker = NULL; 
      // initalize variable arguments
      va_start(marker, fmt);       
      // Get formatted string length adding one for the NULL
      size_t len = _vscprintf(fmt, marker) + 1;               
      // Create a char vector to hold the formatted string.
      vector<char> buffer(len, '\0');
      int nWritten = _vsnprintf_s(&buffer[0], buffer.size(), len, fmt, marker);

      if (nWritten > 0)
      {
         retStr = &buffer[0];
      }            
      // Reset variable arguments
      va_end(marker); 
   }
   return retStr; 
}
*/

void setCPULoad(string sVal, int dispGUI)
{
 int number = 0;
 string m_sBoxCPULoad;
 
 m_sBoxCPULoad = sVal;
 
 if (dispGUI)
 {
   number = atoi(sVal.c_str());
   // mDynBuff->putMsgToStore(MSGID_SET_CPU_LOAD, number);
 }
}

int main(int argc, _TCHAR* argv[])
{
	long LastTimeIn=0;	
	long LastTimeInMS = 0;	
	int RValue = false;
	int Counter=0;	
	int nSec=0;
	int nOpenFileToken = 0;
	int RingBuffSize= 10;
	char tmpchr;
	int CaptureModeHex = 0;
	char MData[200];
  //unsigned int *nLen;
	//double nTest;

#define FILE_OUTPUT

#ifdef FILE_OUTPUT
	char *FileNameF = "TimeSt.log";
	FILE *fi = NULL; 
  
 // open the file for input:	
 if ( (fi = fopen(FileNameF, "a+") ) != NULL)
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
	  
   // fprintf(fi, "Start time: %d\n", Get1msTime());
#endif// FILE_OUTPUT

  //*********************TEST MODULE**************
  
  
	  unsigned long uResult = 0;
	  int NbrOfReadBytes=0;
	  int i=0;
	  double fPow = 0;
	  char ReceiveBuffer[50];
	  memset(ReceiveBuffer, '*', 50);
	  

       // t = new Trace(1,1,1);
		// CommPort CmPort(3, CommPort::br38400);
		//CommPort CmPort(3);
		//CmPort.SetBaudRate(CommPort::br38400);
		
		for (i=0; i<101; i++)
		{
		  // printf ("[%d]-%c ", i, ReceiveBuffer[i], ReceiveBuffer[i]);
			fPow = pow(2.0 ,i);
			fprintf(fi, "2->%d = %0.0f\n",i, fPow);
			printf("2->%d = %0.0f\n",i, fPow);
		}

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif
 
	   // return 0; 
		//ChangeBuffer(ReceiveBuffer, 16);

#define YS_11JULY2007
#ifdef YS_11JULY2007
 //printf ("-------------------------------------\n\n");
// 
//t->TRACEY_TEST("TRACEY_Test %d line\n", 34);
//t->TRACEY     ("TRACEY %d line\n", 34);
//t->getExistance();


string sStrVal;
// std::stringstream str;
string buffer;
int nMsgId = 0;	
const int nMsgsInPool = 255;
int CpuLoadAvg = 551;
//CString str;
// s = str( format(" %d %d ") % 11 % 22 );

//str.Format("%.2f%%", (float)CpuLoadAvg/10);
//sStrVal.snprintf
 sprintf (MData, "%.2f%%", (float)CpuLoadAvg/10);
//sStrVal. ("%.2f%%", (float)VcbOtherVcbDataStruct.CpuLoadAvg); // do not forget to divide to 10!	   
// str << setprecision(2) << ((float)CpuLoadAvg/10);       
sStrVal = ((float)CpuLoadAvg/10);
sStrVal = MData;
setCPULoad(sStrVal, 1);
// setCPULoad(str.str(), 1); 


//**********************************************
//*************MAIN LOOP*****************//
 do 
 {    
	++Counter;    
  
  // NbrOfReadBytes = CPort->ReadFromPort(ReceiveBuffer, 128);
  if (NbrOfReadBytes)
	{
		printf ("NbrOfReadBytes: %d, %s\n", NbrOfReadBytes, ReceiveBuffer);
		if (CaptureModeHex == 1) // Hex binary
    {
     for (int j=0; j < NbrOfReadBytes; j++)
	    {
	      tmpchr=(unsigned char)*(ReceiveBuffer-NbrOfReadBytes+j);
	      sprintf(MData,"\\x%X",tmpchr);
	      // SendStr(MData,origin,strlen(MData));
				printf ("%s",MData);
	     }
    }
		
		//for (i=0; i<ReadBytes; i++)
		//{
		//  printf ("[%d]%c (0x%X) ", i, ReceiveBuffer[i], ReceiveBuffer[i]);
		//}
	  
	}

  if ((( Get1msTimeMS() - LastTimeInMS)>1000-1) || (LastTimeInMS > Get1msTimeMS() ))
	{	
	 // uResult = CPort->WriteToPort("COM-PORT-TEST ",14);
     // uResult = CmPort.WriteToPort("COM-PORT-TEST ",14);
	 // ReadFromPort:	 
	 // printf ("Time: %ld. WriteToPort: %ld bytes\n",Get1msTimeMS(), uResult);
	 LastTimeInMS = Get1msTimeMS();
    }   
   /*
	if ((( Get1msTime() - LastTimeIn)>100-1) || (LastTimeIn > Get1msTime() ))
	{	
	 //printf ("NO-PENT time: %u, Pa3HocTb: %d\n", t.GetElapsedTimeMks(), (t.GetElapsedTimeMks() - LastTimeInMS));
     LastTimeIn = Get1msTime();
	 //RND_Array(1);
	}
	*/
	// control of endless loop (may be also in monitor.cpp)
	if (_kbhit())  // has anything been pressed from keyboard ?
	{       
  	 NewChar=(unsigned char)_getch();
	 if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
	 {
	  RValue = true; // END mark
	 }
	 if (NewChar == 'd')  // CTRL-X   pressed
	 {
	   if (1 == CaptureModeHex) 
		   CaptureModeHex = 1;
		 else
 		   CaptureModeHex = 0;
	 }
	}

}while (!RValue);  

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif
 
 // ClosePort:
 // CPort->~CommPort();
 // delete CPort;
 // t->~Trace();

#endif //ifdef YS_11JULY2007

 printf ("Application complete.\n");

return 0;
}


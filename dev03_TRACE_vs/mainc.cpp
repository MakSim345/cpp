#include "gen.h"
#include "trace.h"
// #include "utils.h"
#include "commport.h"
#include "RingBuffer.h"
#include  <math.h>

#include "ctimer.h" 
#include <iostream>

#include <sstream>
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

//Trace *t;

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

void i_trace(stringstream sDest)
{
  string s_TestStr;
  sDest.str("");
  printf(s_TestStr.c_str());
}

string getStr()
{
	return "test";
}

int getInt()
{
	return 525345;
}

// Trace trc(1,1);
Trace* Trace::m_gInstance = 0;

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
    errno_t err;

 // open the file for input:	
 if ( (err = fopen_s(&fi, FileNameF, "a+") ) != 0)
  {
   printf ("file %s was not open\n", FileNameF);
   // getchar(); //
   nOpenFileToken = 0;
  }
 else
  {
   // printf ("file %s was open succesfully\n", FileNameF);
   nOpenFileToken = 1;
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
 // t = new Trace(1,1);
 //t = new Trace(1,1,0);
 
 /*
  for (i=0; i<101; i++)
  {
   // printf ("[%d]-%c ", i, ReceiveBuffer[i], ReceiveBuffer[i]);
   fPow = pow(2.0 ,i);
   fprintf(fi, "2->%d = %0.0f\n",i, fPow);
   printf("2->%d = %0.0f\n",i, fPow);
  }
*/

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif

#define YS_11JULY2007
#ifdef YS_11JULY2007
 //printf ("-------------------------------------\n\n");
 
    int test_q = 234;
    
    Trace::Initialize(1,1);
    
    // Trace::Shutdown();

    LOG("Test 2 - i: " << showbase << hex << i);
    i = 0xAA;
	int test[12] = {1,23,3,42342,5,6,7,58,9,4310,234};
	list<int> mylist(test, test + sizeof(test) / sizeof(int));

	TRACE("Test 1 - i: " << showbase << hex << i << ", scientific: " << scientific << 34234.2342342 << getStr());
	TRACE("Test 2 - i: " << showbase << hex << i);
	
	//trc.getStream().width(6);
	//trc.getStream().fill('0');
	//trc.getStream().flags( ios::dec || ios::right || ios::showbase);
	
	// TRACE("Hex:"<<showbase << hex << 23);
	
	TRACE_HEX("Test 3 - empty");
	TRACE_HEX(ReceiveBuffer);
	TRACE ("This is a line after all those changes");
	for (i = 0; i<25; i++)
	  TRACE ("Iteration "<< i);
	
	list<int>::const_iterator it = mylist.begin();
	while( it != mylist.end())
	{
		TRACE(*it);
		it++;
	}

string buffer;  
int nMsgId = 0;	
const int nMsgsInPool = 255;
int CpuLoadAvg = 551;


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
	      // sprintf(MData,"\\x%X",tmpchr);
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
	 printf ("Time: %ld. \n",Get1msTimeMS());
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


// dev001.cpp : Defines the entry point for the console application.
//

#include "gen.h"
#include "monitor.h"
#include "utils.h"
#include "timectr.h"
#include "commport.h"
#include "comminc.h"
#include "virt_class.h"
#include "RingBuffer.h"
#include "NetworkServices.h"

#define STRICT 1 
#include <windows.h>
//#include <Mmsystem.h>
//#include <iostream.h>
#include <stdio.h>

#include <sys/timeb.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "TCHAR.h"

long g_lTimeTick = 0;
int DispSync=0;
int MainNewChar=0;

//unsigned int DOIrisReadThread(IRIS_Node *pINode, char *buffer, unsigned long length);

int GetPortNumberFromUser()
{
 	unsigned short tmpPortNumber;
	int RetVal = 0;
	printf ("\nPlease enter serial port number...");
    tmpPortNumber = getch();
	//RetVal = _wtoi((wchar_t)&tmpPortNumber);
	printf ("\nYou've choose serial port number %d, 115200 bps\n", RetVal);
	if (RetVal<=0 || RetVal>4)
	{
		 printf ("Sorry, serial port number %d is out of range. Set #1\n", RetVal);
		 RetVal = 1;
	}
	return RetVal;
}

VOID CALLBACK interrupt_set(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) 
{ 
  static long g_lTime = 0;
  printf ("Time: %ld, diff = %d\n", dwTime, dwTime - g_lTime );  
  g_lTimeTick += TIME_TICK_INTERVAL;
  g_lTime = dwTime;  
}
  
typedef struct
{
    int   nCRC1;
    double fCRC1;
	int   nCRC2;
	//int   nCRC3;
	
	//double fCRC2;
	//double fCRC3;
}
TMP_Struct;

void Function1(int* IntAnt)
{
  *IntAnt=1203;
}

void Function2(int& IntAnt)
{
  //int nNum = 1203;
	IntAnt = 6205;
}


int ConvAsciiHexToInt(int msPart,int lsPart)
{
  int ret = 0;

  if (msPart >= 48 && msPart <= 57) // 0 - 9
  {
    ret = 16 * (msPart-48);
  }
  if (msPart >= 65 && msPart <= 70) // A - F
  {
    ret = 16 * (msPart - 55);
  }

  if (lsPart >= 48 && lsPart <= 57) // 0 - 9
  {
    ret = ret + (lsPart-48);
  }
  if (lsPart >= 65 && lsPart <= 70) // A - F
  {
    ret = ret + (lsPart - 55);
  }

  return ret;
}


unsigned char ASCIIhexToBin(char c1, char c2)
  {
  c1 = c1 - '0';
  if (c1 > 9) c1 = c1 - 7;
  c2 = c2 - '0';
  if (c2 > 9) c2 = c2 - 7;
  return ( 16*c1 ) + c2;
  }


CommPort *CPort[NBR_OF_PORTS];
int PortNumber = 1;
CTRACE t(1,1);

int main(int argc, char *argv[], char *envp[]) 
{
	long LastTimeIn=0;	
	long LastTimeInMS = 0;	
	int RValue = false;
	int Counter=0;	
	int nSec=0;
	int nOpenFileToken = 0;
    int BigMessageSet =0;
	//double nTest;
    //unsigned char IRISbuffer[50];
    int RingBuffSize= 10;
	unsigned long uResult = 0;
	char t1[50];
	char ReceiveBuffer[500];
    int NbrOfReadBytes=0;
    unsigned char tmpchr;
	unsigned char TstArr[100];
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
    // printf ("TEST MODULE. BEFORE time: %ld\n", Get1msTimeMS()); 
    double TstDouble = 0.0;
	unsigned char nRes = 0;
	int NumbOfChars = 27;
  
// 	printf ("ASCIIhexToBin() = %c\n", ASCIIhexToBin('3', '1') );
	
	VirtualDriver *VDriver;	
	//InherDriverA q;

	//VDriver = new InherDriverA();
    //VDriver->SetInteger(3);
	//return 0;

	TMP_Struct tstr;
  
	//tstr.nCRC1=108;
	//tstr.nCRC2=5;
	//tstr.nCRC3=3521;
	tstr.fCRC1=25.7;
	// printf ("sizeof(double)=%d, sizeof(int)=%d\n", sizeof(double), sizeof(int));
    // memcpy((void *)&TstArr, (const void*)&tstr, sizeof(tstr));	
  
	//TstDouble = 38.4;
	//memcpy((void *)&TstArr, (const void*)&TstDouble, 8);	

    for (int j=0; j <sizeof(TstDouble); j++)
    {
	    t.TRACE("[%d]=",j);		
	    t.TRACE("[0x%X]\n", TstArr[j]);
    }
    t.TRACE("\n");
	// memcpy((void *)&TstDouble, (const void*)&TstArr, 8);	
	
    //printf ("TstDouble=%f, 0x%X\n", TstDouble, TstDouble);
	//memcpy((void *)&tr, (const void*)(TstArr+3), 2);
    //printf ("tr=%d, 0x%X\n", tr, tr);
	//printf ("------ 0x%X\n", 0x00AA);
	//printf ("------ %f\n", 25.7 );
  
	
	
	NetworkServices NTs;
    GetVersionString(t1);
	
	t.TRACE("msserial.lib version: %s\n", t1 );
	
	PortNumber =1 ; // GetPortNumberFromUser();
    InitSerialPorts(PortNumber);
  
	// init IRIS message. Emulation of receiving, send it to VCB:
    //Send_1F_Message(30, PortNumber);
	//Send_1F_Message(30, PortNumber);
    //Send_EMPTY_Message(43,PortNumber);
    //Send_EMPTY_Message(44,PortNumber);
	//Send_EMPTY_Message(45,PortNumber);
	//Send_EMPTY_Message(46,PortNumber);
    
    // printf ("CRC: 0x%X\n", NTs.calcCRC(IRISbuffer,2) );
	// Send_TEST_Message(0,1);
	
	// printf ("TEST MODULE. AFTER time: %ld\n", Get1msTimeMS()); 
 	// return 0;
//**********************************************
   int nCtrMsgSend=0;
//*************MAIN LOOP*****************//
 do 
 {    
	++Counter;    
   
	NbrOfReadBytes = ReadRxData(PortNumber, ReceiveBuffer);
  if (NbrOfReadBytes)
	{
		//printf ("NbrOfReadBytes: %d, %s\n", NbrOfReadBytes, ReceiveBuffer);
		// INode->receivePacket(ReceiveBuffer,NbrOfReadBytes);		
		// printf ("NbrOfReadBytes: %d\n", NbrOfReadBytes);
	 	t.TRACE("Received: "); 
		
		for (int j=0; j < NbrOfReadBytes; j++)
	   {
	    tmpchr=(unsigned char) ReceiveBuffer[j];
	    // fprintf(fi, "\\0x%X", tmpchr);
			t.TRACE("\\0x%X", tmpchr); 
			//printf ("\\0x%X",tmpchr);
	   }
	  
	  t.TRACE("\n"); 		
   }
  
	//DOIrisReadThread(INode, ReceiveBuffer, NbrOfReadBytes);

  if ((( Get1msTimeMS() - LastTimeInMS)>1000-1) || (LastTimeInMS > Get1msTimeMS() ))
	{
		if (nCtrMsgSend < 1)
		{
		 //Send_TEST_Message(0,PortNumber);
	   nCtrMsgSend++;
		}
	   //Send_0x20_Message(BigMessageSet, PortNumber);
		//Send_0x23_Message(0, PortNumber);
	  BigMessageSet++;
	/*		
   if(2 == BigMessageSet)
		{
		 BigMessageSet = 0;
	 }
	*/
	 // printf ("Time: %ld. WriteToPort: %ld bytes\n",Get1msTimeMS(), uResult);	 
	 LastTimeInMS = Get1msTimeMS();
    }   
	
	// control of endless loop (may be also in monitor.cpp)
	 RValue=monitor(DispSync);
/*
if (kbhit())  // has anything been pressed from keyboard ?
	{       
   MainNewChar=(unsigned char)getch();
	 if ((MainNewChar & 0xff) == 24)  // CTRL-X   pressed
	 {
	  RValue = true; // END mark
	 }     
	}
*/

}while (!RValue);  

#ifdef USE_OUTPUT_FILE	
 fprintf(fi, "End time: %d\n", Get1msTimeMS());
 if (1 == nOpenFileToken)
   fclose (fi);
#endif

 RemoveSerialPortFromPoll();
 //delete CPort[1];
  
 printf ("\nApplication complete.\n");

return 0;
}


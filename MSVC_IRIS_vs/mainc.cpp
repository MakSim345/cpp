// dev001.cpp : Defines the entry point for the console application.
//

#include "gen.h"
#include "monitor.h"
#include "utils.h"
#include "timectr.h"
#include "commport.h"
#include "comminc.h"
#include "RingBuffer.h"
#include "NetworkServices.h"
#include "iris_if.h"
#include "MessageSimul.h"


#define STRICT 1 
#include <windows.h>
//#include <Mmsystem.h>
#include <iostream>
#include <stdio.h>

#include <sys/timeb.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "TCHAR.h"

long g_lTimeTick = 0;
int DispSync=0;
int MainNewChar=0;

unsigned int DOIrisReadThread(IRIS_Node *pINode, char *buffer, unsigned long length);

int GetPortNumberFromUser()
{
     unsigned short tmpPortNumber;
    int RetVal;
    printf ("\nPlease enter serial port number...");
  tmpPortNumber = getch();
    RetVal = _wtoi(&tmpPortNumber);
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

  CommPort *CPort[NBR_OF_PORTS];
  int PortNumber = 1;
  
    // init TRACE object. (ToFile=1, ToConsole=1)
    CTRACE t(1,1);
    // CTRACE t(1,1, "UserAllegro.log");

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

int main(int argc, char *argv[], char *envp[]) 
{
    long LastTimeIn=0;    
    long LastTimeInMS = 0;    
    int RValue = false;
    int Counter=0;    
    int nSec=0;
    int nOpenFileToken = 0;
    //double nTest;
  unsigned char IRISbuffer[50];
  int RingBuffSize= 10;
    unsigned long uResult = 0;
    //char t1[50];

    char ReceiveBuffer[500];
  int NbrOfReadBytes=0;
  
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
  // char *szDeviceName = new TCHAR[50];
   //printf ("sizeof(double)=%d, sizeof(int)=%d\n", sizeof(double), sizeof(int));
  //memcpy((void *)&TstArr, (const void*)&tstr, sizeof(tstr));    
/*
 for (int j=0; j <sizeof(tstr); j++)
    {
     printf("[%d]=(%c)[0x%X]\n",j, TstArr[j],  TstArr[j]);        
    }
    printf("\n");
*/
   // return 0;
    
    //NetworkServices NTs;
  IRIS_Node *INode;
    //GetVersionString(t1);
    //t.TRACE("msserial.lib version: %s\n", t1 );
    
    PortNumber =1 ; // GetPortNumberFromUser();
  InitSerialPorts(PortNumber);
  
    //INode = new IRIS_Node(compatCode, maxMsg, subsysId);
    INode = new IRIS_Node();
    
    // init IRIS message. Emulation of receiving, send it to VCB:
  //SendRequestMessage(30, PortNumber);
    //SendRequestMessage(30, PortNumber);
  //Send_EMPTY_Message(43,PortNumber);
  //Send_EMPTY_Message(44,PortNumber);
    //Send_EMPTY_Message(45,PortNumber);
    //Send_EMPTY_Message(46,PortNumber);
    
  // printf ("TEST MODULE. AFTER time: %ld\n", Get1msTimeMS()); 
     // return 0;
//*********************************************
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
      DOIrisReadThread(INode, ReceiveBuffer, NbrOfReadBytes);     
        // t.TRACE_HEX(ReceiveBuffer, NbrOfReadBytes); 
   }    

  if ((( Get1msTimeMS() - LastTimeInMS)>1000-1) || (LastTimeInMS > Get1msTimeMS() ))
    {
        nCtrMsgSend++;
        // Send_0x24_Message(30, PortNumber);
        // Send_0x20_Message(nCtrMsgSend, PortNumber);
        // Send_0x20_Message_I(nCtrMsgSend, PortNumber);
    /*        
      SendRequestMessage(34, PortNumber); // \0x1F\0x22\0x29\0x88\0x7E
        SendRequestMessage(32, PortNumber); // \0x1F\0x20\0xE8\0x9\0x7E
        SendRequestMessage(35, PortNumber); // \0x1F\0x23\0xE9\0x49\0x7E
        SendRequestMessage(36, PortNumber); // \0x1F\0x24\0x2B\0x8\0x7E
        SendRequestMessage(56, PortNumber); // \0x1F\0x38\0xE2\0x9\0x7E
        SendRequestMessage(39, PortNumber); // \0x1F\0x27\0x2A\0x48\0x7E
        SendRequestMessage(57, PortNumber); // \0x1F\0x39\0x22\0xC8\0x7E
        SendRequestMessage(37, PortNumber); // \0x1F\0x25\0xEB\0xC9\0x7E
        SendRequestMessage(41, PortNumber); // \0x1F\0x29\0xEE\0xC9\0x7E
        SendRequestMessage(38, PortNumber); // \0x1F\0x26\0xEA\0x89\0x7E
        SendRequestMessage(60, PortNumber); // \0x1F\0x3C\0x21\0x8\0x7E
        SendRequestMessage(118, PortNumber); // \0x1F\0x76\0xD6\0x89\0x7E
        SendRequestMessage(120, PortNumber); // \0x1F\0x78\0x12\0x8\0x7E
        SendRequestMessage(121, PortNumber); // \0x1F\0x79\0xD2\0xC9\0x7E
        SendRequestMessage(47, PortNumber); // \0x1F\0x2F\0xEC\0x49\0x7E
        SendRequestMessage(48, PortNumber); // \0x1F\0x30\0x24\0x8\0x7E
        SendRequestMessage(49, PortNumber); // \0x1F\0x31\0xE4\0xC9\0x7E
        SendRequestMessage(50, PortNumber); // \0x1F\0x32\0xE5\0x89\0x7E
        SendRequestMessage(51, PortNumber); // \0x1F\0x33\0x25\0x48\0x7E
        SendRequestMessage(52, PortNumber); // \0x1F\0x34\0xE7\0x9\0x7E
        SendRequestMessage(53, PortNumber); // \0x1F\0x35\0x27\0xC8\0x7E
        SendRequestMessage(54, PortNumber); // \0x1F\0x36\0x26\0x88\0x7E
        SendRequestMessage(55, PortNumber); // \0x1F\0x37\0xE6\0x49\0x7E        
  */
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
 
 // release serial ports objects: 
 RemoveSerialPortFromPoll();
   
 printf ("\nApplication complete.\n");

return 0;
}


/*********************************************************************

  monitor.cpp
  Savcor IT Oy/JLM
  Borland TURBO C++ 3.0
  31.10.2000 Initial coding
 **********************************************************************/

#include <stdio.h>
#include <conio.h>
#include <dos.h>
//#include <io.h>
#include <string.h>
#include <stdlib.h>
//#include <mem.h>
//#include <fcntl.h>
//#include <allegro.h>


#include "gen.h"
#include "commport.h"
#include "utils.h"
#include "error.h"
#include "monitor.h"
#include "comminc.h"

#define BUFFER_SIZE 150


char OutStr[2*BUFFER_SIZE];

int DispFreq=5;
int FreqCounter=0;
int AddCursor=FALSE;

int CaptureComInput[7]={0,0,0,0,0,0,0};
int CaptureComOutput[7]={0,0,0,0,0,0,0};
int CaptureMode=0;
int CaptureLPT1=0;
int InGraphMode=TRUE;
int TickCounter=0;
int SimSensor=0;
int USSimul=0;
int InpSimul=0;

long   CRC_err_counter = 0;
extern error_type ErrStack[];
extern rstack_type RemovedErrorsStack[];
extern int EStackPtr;  // Error stack pointer
extern int RStackPtr;  // Removed Errors Stack Pointer
extern int MONITOR_PORT;
extern long GPS_TimeoutCounter;

int GPS_TIMEOUT =100000;
long GPS_TimeoutCounter;
BOOL gbConnectGPS_104;
BOOL gbConnectMON_104;
BOOL gbDisplayStatus_104;
int ConnectStatus_104;
int Time_Stamp_Log;
int PING_SAV;
extern int Analog;  // block sending analog messages if need.
extern int Fake_Analog; // send an analogue message emulation
extern int ONTIME;
int LOG_ON;

extern int Lpt1Addr;
extern int LPTActive;	


#ifdef RANDOM_MESSAGE 
 extern int nSize, nCOM;
#endif

int origin=ORIGIN_KB;
int LogOn=0;
int LogPlayOn=0;
long PlayStart;
char LogFileName[20];
int handle;
int NewChar=0;
int NewGChar=0;

#ifdef DEBUG
float debug[41];
char  dstr[500];
char  dstr1[500];
#endif

char RecvBuffer[BUFFER_SIZE];
char *Message;

char tempbuf[BUFFER_SIZE];

int DispWithoutLabels=0;
int GMonActive=FALSE;

int SlowDownKeyCtr=0;
bool kpressed=false;

int InOverFlowCounter = 0;
int OutOverFlowCounter = 0;
/********************************************************************

  Savcor IT Oy/JLM
  Borland TURBO C++ 3.0
  Declaration: Check if character is alhanumeric (Note! Only upper case)
  Call: IsAlpha(character)
  Input:  char character
  Returns:
  28.11.2000 Initial coding

*********************************************************************/

  int IsAlpha(char character)
    {
    if (
         ( (character > 0x2F ) && (character < 0x3A) ) ||
         ( (character > 0x40 ) && (character < 0x5B) )
       )
      {
      return(TRUE);
      }
    else
      {
      return(FALSE);
      }
    }




/********************************************************************

  Declaration: Check if give disp command is valid
  Call: Ret=CheckValidity(token)
  Input:  char * token  given commad
  Returns: int Ret  =1 (if valid)  =0 (if invalid)
  15.03.2001 Initial coding

*********************************************************************/

int CheckValidity(char *token)
  {
  static long Old1msTime=0;
  strcpy(tempbuf,"");
	
  if (!strcmp ("TIME",token))
    {
		sprintf(tempbuf,"%ld ", Get1msTimeMS());	
		}
 
  if (!strcmp ("NG",token))
    {
     sprintf(tempbuf,"%d %d ", GPS_TIMEOUT, (int)GPS_TimeoutCounter);
    }
	
  if (!strcmp ("TCYC",token))
    {
    sprintf(tempbuf,"%ld ",(Get1msTime()-Old1msTime));
    Old1msTime=Get1msTime();		
    }  
  // CRC error counter (HostMsg) 
   if (!strcmp ("CRCE",token))
    {
    sprintf(tempbuf,"%ld ",CRC_err_counter);		
    }
 
	 //GetSystemCount
	 if (!strcmp ("SCT",token))
    {
    sprintf(tempbuf,"%ld ", GetSystemCount());
    }

   if (!strcmp ("OVIN",token))
	 {
	  sprintf(tempbuf,"%d ", InOverFlowCounter);
	 }

	 if (!strcmp ("OVOUT",token))
	 {
	  sprintf(tempbuf,"%d ", OutOverFlowCounter);
	 }

	 if (strlen(tempbuf)>0)
     {
     return(TRUE);
     }
   else
     {
     return(FALSE);
     }

  }


/********************************************************************

  Savcor IT Oy/JLM
  Borland TURBO C++ 3.0
  Declaration: Reset Display
  Call: ResetDisp()
  Input:
  Returns:

  30.11.2000 Initial coding

*********************************************************************/

  void ResetDisp()
   {
   int i;

   for (i=0;i<7;i++)
     {
     CaptureComInput[i]=FALSE;
     CaptureComOutput[i]=FALSE;
     CaptureLPT1=FALSE;
     CaptureMode=0;
     }
   }

/********************************************************************

  Savcor IT Oy/JLM
  Borland TURBO C++ 3.0
  Declaration: Parse received message
  Call: ret=ParseMessage(ReceiveBuffer)
  Input:  char *ReceiveBuffer
  Returns:  char *ret
  01.12.2000 Initial coding  JLM

*********************************************************************/
 void ParseMessage(char *OutMes)
  {
  int i;
  int j=0;
  char token[BUFFER_SIZE];

  strcpy(OutMes,"");
  strcpy(tempbuf,"");

  for (i=1;i<(int)strlen(Message);i++)
    {		

    if (IsAlpha(Message[i]) && ( i < ((int)strlen(Message)-1)))
      token[j++]=Message[i];
    else
      {
       if (j>0)
        {
          token[j]=0;  // end of string
          strcpy(tempbuf,"");				
          CheckValidity(token); 
          if ( (!DispWithoutLabels) && (strlen(tempbuf)>0))
          {
           strcat(OutMes,token);
           strcat(OutMes,"=");
          }
          strcat(OutMes,tempbuf);
					//printf ("OutMes=%s\n",OutMes);
        }
       j=0;
			} // else
    }
  }

/********************************************************************

  Savcor IT Oy/JLM
  Borland TURBO C++ 3.0
  Declaration: Intrepret and display monitor message
  Call:char * InterpretMessage(Message)
  Input:  char * Message
  Returns:
  23.11.2000 Initial coding

*********************************************************************/

void InterpretMessage()
   {
   char t1[100];	 
   int NbrOfFatalErrors=0;
   int NbrOfSevereErrors=0;
   int NbrOfNormalErrors=0;
   int NbrOfWarnings=0;
   int NbrOfInfo=0;
   int i;
	 char bigbuffer[500];

  if (Message[0] == 'D')
    {

    // Display frequency setting

    if ( (Message[1] > 0x2F) && (Message[1] <0x3A) )
      {
       if ( (Message[2] > 0x2F) && (Message[2] <0x3A) )
         DispFreq=(int)(Message[1]-0X30)*10+(int)(Message[2]-0x30);        
       else        
         DispFreq=(int)(Message[1]-0x30);
			
       FreqCounter=DispFreq;
       sprintf(tempbuf,TX0019,FreqCounter);
       SendStr(tempbuf,origin,strlen(tempbuf));
      }
     
		 // remote monitor sent an exit command (somehow it is different than remoute GPS monitoring)
		 if ((Message[1]=='Q') && (Message[2]=='U') && 
				 (Message[3]=='I') && (Message[4]=='T'))//"QUIT" 
		 {	
			 //SendCommand_104 (strlen(TX0071), TX0071);
			 gbConnectGPS_104 = FALSE;
			 gbConnectMON_104 = FALSE;			 
		 }

    // COM port redirection

    if ( (Message[1] == 'C') && (Message[2] == 'O')
        && (Message[3] == 'M') )
      {
      if  ( (Message[4] > 0x30) &&  (Message[4] < 0x37 ))
        {
        if ( Message[5] == 'I')
          {
          CaptureComInput[Message[4]-0x30]=TRUE;
          sprintf(tempbuf,TX0020,(int)Message[4]-0x30);
          SendStr(tempbuf, origin, strlen(tempbuf));            
          }
        if ( Message[5] == 'O')
          {
          CaptureComOutput[Message[4]-0x30]=TRUE;
          sprintf(tempbuf,TX0021,(int)Message[4]-0x30);
          SendStr(tempbuf, origin, strlen(tempbuf)); 
          }
         if ( Message[6] == 'H')
          {
          CaptureMode=1;
          }
        else
          {
          CaptureMode=0;
          }
        }
      }

    // Version number asked ?

    if ((Message[1]=='V') && (Message[2]=='E') && ( Message[3]=='R'))
      {
			sprintf(t1,TX0023,__DATE__,__TIME__);
      strcat(tempbuf,t1);
      SendStr(tempbuf,origin,strlen(tempbuf));
      strcpy(bigbuffer,"\n\r");			

if (PING_SAV)
     strcat(bigbuffer,"PING messages sending ON\n\r");


#ifdef TRIMBLE_950
   strcat(bigbuffer,"TRIMBLE_950\n\r");
#endif

#if defined PENTIUM
      strcat(bigbuffer,"PENTIUM\n\r");
#endif

#ifdef RANDOM_MESSAGE
      strcat(bigbuffer,"RANDOM_MESSAGE ON\n\r");
			sprintf(t1, "RND_MESSAGE size %d\n\r", nSize);
      strcat(bigbuffer,t1);			
			sprintf(t1, "RND_MESSAGE PORT %d\n\r", nCOM);			
			strcat(bigbuffer, t1);
#endif

		strcat(bigbuffer, COMFILE_VERSION);
			
    SendStr(bigbuffer,origin,strlen(bigbuffer));
  }
   
    // Give directory
    if ((Message[1]=='C') && (Message[2]=='A') && ( Message[3]=='T'))
      {
      system("dir *.log /w");
      }

    // Toggle Label display
    if ((Message[1]=='L') && (Message[2]=='B') && ( Message[3]=='L'))
      {
      if (DispWithoutLabels)
        {
        DispWithoutLabels=FALSE;
        sprintf(tempbuf,TX0024);
			  SendStr(tempbuf,origin,strlen(tempbuf));
        }
      else
        {
        DispWithoutLabels=TRUE;
        sprintf(tempbuf,TX0025);
			  SendStr(tempbuf,origin,strlen(tempbuf));
        }
      }

    // Display Errors
    if ((Message[1]=='E') && (Message[2]=='R') && ( Message[3]=='R'))
      {
      if (Message[4] == 'R')
        {
        // display removed errors
        for (i=0; i<RStackPtr;i++)
          {
          sprintf(tempbuf,TX0035,RemovedErrorsStack[i].Code,
                  RemovedErrorsStack[i].Time,RemovedErrorsStack[i].Counter);
          if (Message[4] == 'R')
           {
   					SendStr(tempbuf,origin,strlen(tempbuf));
            }
          }
        }
      else
        {
        for (i=0; i<EStackPtr;i++)
          {
          sprintf(tempbuf,TX0034,ErrStack[i].Code,ErrStack[i].Par1,
                 ErrStack[i].Par2,ErrStack[i].Time,ErrStack[i].Counter);
          if (ErrStack[i].Code < 5000)
            {
            if (Message[4] == 'F')
              {
							 SendStr(tempbuf,origin,strlen(tempbuf));
							}
            NbrOfFatalErrors++;
            }
          else if (ErrStack[i].Code < 10000)
            {
            if (Message[4] == 'S')
              {
						   SendStr(tempbuf,origin,strlen(tempbuf));
              }
            NbrOfSevereErrors++;
            }
          else if (ErrStack[i].Code < 15000)
            {
            if (Message[4] == 'N')
              {
						   SendStr(tempbuf,origin,strlen(tempbuf));
              }
            NbrOfNormalErrors++;
            }
          else if (ErrStack[i].Code < 20000)
            {
            if(Message[4] == 'W')
              {
						   SendStr(tempbuf,origin,strlen(tempbuf));
              }
            NbrOfWarnings++;
            }
          else
            {
          if(Message[4] == 'I')
            {
						  SendStr(tempbuf,origin,strlen(tempbuf));
            }

            NbrOfInfo++;
            }
          }

          if ( Message[4]=='A' )
            {
            sprintf(tempbuf,TX0029,NbrOfFatalErrors);
					  SendStr(tempbuf,origin,strlen(tempbuf));
            
						sprintf(tempbuf,TX0030,NbrOfSevereErrors);
					  SendStr(tempbuf,origin,strlen(tempbuf));

						sprintf(tempbuf,TX0031,NbrOfNormalErrors);
					  SendStr(tempbuf,origin,strlen(tempbuf));
            
						sprintf(tempbuf,TX0032,NbrOfWarnings);
            SendStr(tempbuf,origin,strlen(tempbuf));
            
						sprintf(tempbuf,TX0033,NbrOfInfo);
            SendStr(tempbuf,origin,strlen(tempbuf));
            
						sprintf(tempbuf,TX0036,RStackPtr);
						SendStr(tempbuf,origin,strlen(tempbuf));

            }

          }
        }
    }				
		
//**********104 connection commands*********'

if ((Message[1]=='C') && (Message[2]=='O') && ( Message[3]=='N') && 
		  (Message[4]=='N') && (Message[5]=='E') && (Message[6]=='C') && (Message[7]=='T'))//"CONNECT" == connect to ...
  {  

	if (0)//strcmp(gMARK, "master") == 0) 	 
	{
	 if (!gbConnectGPS_104)
	 {		 
		 gbConnectGPS_104  = TRUE;
		 //ConnectStatus_104 = CONNECT_PROCESSING;
		 //printf ("Before SendCommand_104(%d, %s)\n", strlen(TX0125), TX0125);
#ifdef TRIMBLE_950
     if (SendCommand_BD950(DUMP)) // send "Hi"
			{      
			 sprintf(tempbuf, TX0129); //"104: CONNECTING.....  \n"
       SendStr(tempbuf, origin, strlen(tempbuf));	
			 ConnectStatus_104 = CONNECT_ESTABLISHED;
			 LOG_ON = 1;
			}		 		 
#else // usual app
		 //if (SendCommand_104(strlen(TX0125), TX0125)) // send "HELLO"
			//{      
			// sprintf(tempbuf, TX0129); //"104: CONNECTING.....  \n"
      // SendStr(tempbuf, origin, strlen(tempbuf));			
		  //}		 		 
#endif // TRIMBLE_950
		}	
	 }
	else // not allow to active connect in SLAVE mode!
	{
	  sprintf(tempbuf, TX0100);
    SendStr(tempbuf, origin, strlen(tempbuf));			
	}
  } 	

 if ((Message[1]=='C') && (Message[2]=='O') && ( Message[3]=='N') && 
		  (Message[4]==' ') && (Message[5]=='-') && ( Message[6]=='S') &&
			(Message[7]=='Y') && (Message[8]=='N') && ( Message[9]=='C'))
			//"CON -SYNC" == syncronize time with 104
  {
	 if(0) // (strcmp(gMARK, "master") == 0) 	 
		{	
			SendSynchroTime_104();
		}
   else // not allow to active connect in SLAVE mode!
	  {
	   sprintf(tempbuf, TX0100);
     SendStr(tempbuf, origin, strlen(tempbuf));			
	  }
	}	 
//**********104 disconnection command*********'

 if ( gbConnectGPS_104 == 0) 
 {	
	if ((Message[0]=='Q') && (Message[1]=='U') && ( Message[2]=='I') && (Message[3]=='T')) //
   {   
		if (0)// (SendCommand_104(strlen(TX0126), TX0126))  // BYE...
			{
       gbConnectGPS_104 = FALSE;
			 gbConnectMON_104 = FALSE;
			 ConnectStatus_104= NO_CONNECT;
			 LOG_ON = 0;
			 sprintf(tempbuf, TX0127);
       SendStr(tempbuf, origin, strlen(tempbuf));
			}		 
    } 
	} 
#ifdef TRIMBLE_950
//**********104 connection commands END*********'
 if ( gbConnectGPS_104)
 {	 
//**********command GETSTAT1*********'
  if ((Message[0]=='G') && (Message[1]=='E') && ( Message[2]=='T') && (Message[3]=='S') && ( Message[4]=='T')
	    && (Message[5]=='A') && ( Message[6]=='T')) //
		{     
		 //printf ("Command GETSTAT1 ready to be sent to GPS card!\n");
     SendCommand_BD950(GETSTAT);
		} 
//**********command GETSERIAL*********'
  if ((Message[0]=='G') && (Message[1]=='E') && ( Message[2]=='T') && (Message[3]=='S') && ( Message[4]=='E')
	    && (Message[5]=='R') && ( Message[6]=='I') && (Message[7]=='A') && ( Message[8]=='L')) //
		{     
		 //printf ("Command GETSERIAL ready to be sent to GPS card!\n");
     SendCommand_BD950(GETSERIAL);
		} 
//**********command GETSERIAL*********'
  if ((Message[0]=='G') && (Message[1]=='E') && ( Message[2]=='T') && (Message[3]=='R') && ( Message[4]=='A')
	    && (Message[5]=='W')) //
		{     
		 //printf ("Command GETRAW ready to be sent to GPS card!\n");
     SendCommand_BD950(GETRAW);
		} 

//**********command DUMP*********'
  if (( Message[0]=='D') && (Message[1]=='U') && (Message[2]=='M') && ( Message[3]=='P')) 
		{     		 
	   //printf ("Command ready to be sent Dump from a GPS card!\n");
	   SendCommand_BD950(DUMP);
		} 

//**********command STATUS*********'
  if (( Message[0]=='S') && (Message[1]=='T') && (Message[2]=='A') && ( Message[3]=='T')) 
		{     		 
	   //printf ("Command ready to be sent Dump from a GPS card!\n");
	   SendCommand_BD950(STATUS);
		} 

//**********command CLEAR*********'
  if (( Message[0]=='C') && (Message[1]=='L') && (Message[2]=='E') && ( Message[3]=='A') && ( Message[4]=='R')) 
		{     		 
	   //printf ("Command ready to be sent Dump from a GPS card!\n");
	   SendCommand_BD950(CLEAR);
		} 

//**********command CLEAR*********'
  if (( Message[0]=='P') && (Message[1]=='O') && (Message[2]=='S')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   SendCommand_BD950(POSITION);
		} 
//**********command CLEAR*********'
  if (( Message[0]=='S') && (Message[1]=='A') && (Message[2]=='T') && ( Message[3]=='I') && 
		  ( Message[4]=='N') && ( Message[5]=='F') && ( Message[6]=='O')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   SendCommand_BD950(SATINFO);
		} 
//**********command CLEAR*********'
  if (( Message[0]=='S') && (Message[1]=='E') && (Message[2]=='S') && ( Message[3]=='S') && 
		  ( Message[4]=='I') && ( Message[5]=='O') && ( Message[6]=='N')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   SendCommand_BD950(SESSION);
		} 
//**********command CLEAR*********'
  if (( Message[0]=='P') && (Message[1]=='O') && (Message[2]=='W') && ( Message[3]=='E') && 
		  ( Message[4]=='R')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   SendCommand_BD950(POWER);
		} 
//**********command CLEAR*********'
  if (( Message[0]=='N') && (Message[1]=='E') && (Message[2]=='X') && ( Message[3]=='T')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   SendCommand_BD950(NEXT);
		} 
//**********command CLEAR*********'
  if (( Message[0]=='C') && (Message[1]=='O') && (Message[2]=='N') && ( Message[3]=='T') && 
		  ( Message[4]=='R') && ( Message[5]=='O') && ( Message[6]=='L')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   SendCommand_BD950(CONTROL);
		} 
//**********command CLEAR*********'
  if (( Message[0]=='P') && (Message[1]=='O') && (Message[2]=='S')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   SendCommand_BD950(POSITION);
		} 
//**********command CLEAR*********'
  if (( Message[0]=='O') && (Message[1]=='N') && (Message[2]=='E')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   SendCommand_BD950(ONE);
		} 
	//**********command CLEAR*********'
  if (( Message[0]=='T') && (Message[1]=='W') && (Message[2]=='O'))
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   SendCommand_BD950(TWO);
		} 
	//**********command CLEAR*********'
  if (( Message[0]=='T') && (Message[1]=='R') && (Message[2]=='E'))
	 {    		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   SendCommand_BD950(TRE);
		} 
	//**********command CLEAR*********'
  if (( Message[0]=='F') && (Message[1]=='O') && (Message[2]=='R')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   SendCommand_BD950(FOR);
		} 
//**********command LOG - ULOG*********'
 if (( Message[0]=='L') && (Message[1]=='O') && (Message[2]=='G')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   LOG_ON = 1;
		} 
 if (( Message[0]=='U') && (Message[1]=='N') && (Message[2]=='L') && (Message[3]=='O') && (Message[4]=='G')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   LOG_ON = 0;
		} 
 if (( Message[0]=='S') && (Message[1]=='T') && (Message[2]=='O') && (Message[3]=='P')) 
		{     		 
	   //printf ("Command ready to be sent POS from a GPS card!\n");
	   LOG_ON = 0;
		} 
 //**********commands END*********'
	} // if ( gbConnectGPS_104)
#endif // #ifdef TRIMBLE_950
}

/********************************************************************

  Savcor One Oy/YS
  VC++ / DJGPP
  Declaration: function converts an unsigned value to binary format,
  	           presents it in the char array sPtr. 
  Call: displayBits
  Input: Val - any value, like 0xE9; sPtr - result array of char.
  Returns: No returns, only result is changing an input array.
  10.02.2004 YS

*********************************************************************/
void DisplayBits(unsigned Val, char* sPtr)
{
 unsigned   c;
 //unsigned   dispMask=1<<31;
 unsigned   dispMask=1<<7;
 int        nBin, n;
 unsigned int ValueBits;
 int Byte1 = 8; 
 //int Byte2 = 16; 
 //int Byte4 = 32; 
 
 
 ValueBits = Byte1;
 n=0;
 for (c = 1; c<=ValueBits; c++)
 {
	 nBin = Val & dispMask ? 1 : 0 ;
	 if (nBin)
	   sPtr[n] = '1';
	 else
	   sPtr[n] = '0';
	 Val<<=1;
	 if ((c%8 == 0) )
		 {
		  sPtr[n+1] = ' ';
          n++;
		 }
	 n++;
 } 
 sPtr[Byte1+1]=0;
}


  // How to use it:
	/*
  char sPtr[35];
  unsigned int Test
  displayBits(Test, sPtr);
  TRACE ("Test  = 0x%X, %s\n",Test, sPtr); 
  */

/********************************************************************
  SLAVE
  Savcor IT Oy/JLM/YS
  Borland TURBO C++ 3.0
  Declaration: Monitor program that can be used from the keyboard
               from the serial line and from remote terminal such as 
							 a RoadRunner computer or a laptop connected to the RR
  Call: ret=monitor(Dsync)
  Input: int Dsync = TRUE if display is OK
  Returns: int ret = TRUE quit the program, FALSE don't quit
  23.11.2000 Initial codin
*********************************************************************/

int monitor(int DSync)
{
  char InputQueue[20];
  static int RecvPtr =0;
  static char OutStr[2*BUFFER_SIZE];
  static int Status;
  //static unsigned long TimeoutCounter=0;
  static int WaitCommandLine=FALSE;
  //char sPtr[15];

  // wait for next character
   NewChar=0;
  
   if (kbhit())  // has anything been pressed from keyboard ?
   {       
	   NewChar=(unsigned char)getch();
	   origin=ORIGIN_KB;       
		 GPS_TimeoutCounter=0;
	   //TimeoutCounter=0;
	 }
  // printf ("monitor. in\n");
  /*
	if (ReadRxData(MONITOR_PORT,InputQueue))  // anything from remote terminal ?
    {     
		 NewChar=InputQueue[0];
     origin=MONITOR_PORT;     
		 GPS_TimeoutCounter=0;
		 //TimeoutCounter=0;
    }
 */
	//printf ("monitor. 2\n");

	if (NewChar)
   {		
    if ( (NewChar == 'D') || (NewChar == 'd') )
      {
      WaitCommandLine=TRUE;
      Status=DISPLAY_STOPPED;			
      RecvPtr=0;
      ResetDisp();
		  SendStr("\n\n\r>D",origin,5);
      }
    else
      {
      if (WaitCommandLine)
        {
        sprintf(tempbuf,"%c",NewChar);
        SendStr(tempbuf, origin, strlen(tempbuf));
        }
			}

    if (RecvPtr >= BUFFER_SIZE)
      {
       SendStr(TX0026,origin,strlen(TX0026));
       RecvPtr=0;
      }

    if ( ((NewChar & 0xff) == 24) && (!GMonActive) )  // CTRL-X   pressed
    {		
		  return(TRUE);
    }

    if (WaitCommandLine)
      {
        RecvBuffer[RecvPtr++]=NewChar;
      }

    if  (NewChar == 13)    // End of Line
     {			
	    SendStr("\r\n",origin,2);				
      RecvBuffer[RecvPtr]=0;
      // convert the message to upper case
      Message=strupr(RecvBuffer);      
			InterpretMessage();
      RecvPtr=0;
      WaitCommandLine=FALSE;
      Status=DISPLAY_RUNNING;					
			}
   }

  // Check if something has to be sent
  if ( Status==DISPLAY_RUNNING )
  {		
   if (FreqCounter-- <= 0)
   {        
	  	ParseMessage(OutStr);
      if (strlen(OutStr)>0)
			{ 
        strcat(OutStr,"\n\r");
        sprintf(tempbuf,"%s",OutStr);					
			  SendStr(tempbuf,origin,strlen(tempbuf));
			}
      else
			  Status=DISPLAY_STOPPED;				

      FreqCounter=DispFreq;
   }

	 if (GPS_TimeoutCounter++ > (long)GPS_TIMEOUT) 
	 {         
		 //printf ("GPS_TimeoutCounter=%d\n", GPS_TimeoutCounter);
	 	 //Status=DISPLAY_STOPPED;
     //ResetDisp();					  
     //SendStr(TX0027,origin,strlen(TX0027));
   }
	}


 return(FALSE);
 }


/********************************************************************

  Savcor IT Oy/YS
  Declaration: Function reads system's date and time, creates a data 
	             array in memory and send it to the remote 104 computer 
							 using function SendCommand_104. Data array in memory 
							 consists command sequence SYNC and current Data/Time in
							 specific DOS format.
  Call: SendSynchroTime_104()
  Input:  none
  Returns: none
  14.05.2003 Initial coding  YS

********************************************************************/

void SendSynchroTime_104()
{
 char * sSync = "SYNC";		
/*
 struct time t;
 struct date d;   		

//step 1:	get local date and time
 gettime(&t);    
 getdate(&d);		
//step 2: create a data array in memory
 memcpy((void *)tempbuf, (const void*)sSync, strlen(sSync));	
 memcpy((void *)(tempbuf+strlen(sSync)), (const void*)(&d), sizeof(d));	
 memcpy((void *)(tempbuf+strlen(sSync)+sizeof(d)), (const void*)(&t), sizeof(t));	
//step 3: send this data array to remote computer.  
  gbConnectMON_104 = TRUE;
 if (SendCommand_104(strlen(sSync)+sizeof(d)+sizeof(t), tempbuf)) 
 {
   sprintf(tempbuf, TX0133); // "Date and time synchronizing..."
   SendStr(tempbuf, origin, strlen(tempbuf));       
 }			
//step 4: kind of disconnecting.
 */ 
 gbConnectGPS_104 = FALSE;
 gbConnectMON_104 = FALSE;	
 ConnectStatus_104= NO_CONNECT;
}

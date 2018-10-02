/*********************************************************************

  comminc.cpp
  
**********************************************************************/


#include "gen.h"
#include "error.h"
#include "utils.h"
#include "commport.h"
#include "NetworkServices.h"

#define RX_BUF_SIZE 500
#define TX_BUF_SIZE 500

int ActivePort[7]={FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE};

char tmpbuf[100];

// Port number variables
int BASEST_PORT;
int CON_PORT;
int MONITOR_PORT;
int GPS1_PORT;
int GPS2_PORT;
int DEBUG_PORT;
int PLC_PORT;
int HOST_PORT;

extern int CaptureComOutput[];
extern int CaptureComInput[];
extern int CaptureMode;
extern int origin;

extern int InOverFlowCounter;
extern int OutOverFlowCounter;

extern CommPort *CPort[];
extern CTRACE t;

#define DEST 0 // error and info text to the display and to the monitor


//comm_port *com_port[7];

/*
char COM4_RxBuf[RX_BUF_SIZE];
char COM4_TxBuf[TX_BUF_SIZE];
int COM4_RxHead=0;
int COM4_TxHead=0;
int COM4_RxTail=0;
int COM4_TxTail=0;

int com4address=0x2E8;
*/

extern BOOL gbConnectGPS_104;
extern BOOL gbConnectMON_104;

/********************************************************************

  Declaration: Reset all of the interrupts of all serial ports
  Call: ResetInterrupts()
  Input: nothing
  Returns: nothing
  08.11.2000 Initial coding

******************************************************************** */

void ResetSerialInterrupts()
{
  //dzcomm_closedown();
}

/********************************************************************

  Declaration: 
  Call: 
  Input: nothing
  Returns: nothing
  
******************************************************************** */

void RemoveSerialPortFromPoll()
{
  for (int i=1; i<NBR_OF_PORTS+1;i++)
	{
     if (TRUE == ActivePort[i])
			 delete CPort[i];
	}  
}

/********************************************************************

  Declaration: Initialize all serial ports that are asked in ini-file.
  Call: InitSerialPorts()
  Input: None
  Returns: Nothing
  01.11.2000 Initial coding

*********************************************************************/

void InitSerialPorts(int PortNumber)
  {
   int i = 0;
   //comm tmp_port;   
   // char IniFileName[15];

   // Create an array of comm-ports:
	 CPort[PortNumber] = new CommPort(PortNumber, CommPort::br115200);
   ActivePort[PortNumber]=TRUE;	
   
/*
   dzcomm_init();  
  // set port numbers according to the INI-file

  if (!GetProfileInt("[COMMUNICATION_PORTS]",
       "COMPORT_2",0,&BASEST_PORT))
    {
    AddError(WARNING007,0,0,3);
    }
  
	 if (!GetProfileInt("[COMMUNICATION_PORTS]",
       "COMPORT_1",0,&CON_PORT))
    {
    AddError(WARNING007,0,0,2);
    }
	 if (!GetProfileInt("[COMMUNICATION_PORTS]",
       "COMPORT_3",0,&PLC_PORT))
    {
    AddError(WARNING007,0,0,22);
    }

  if (!GetProfileInt("[COMMUNICATION_PORTS]",
       "MonitorPort",0,&MONITOR_PORT))
    {
    AddError(WARNING007,0,0,6);
    }

	 if (!GetProfileInt("[COMMUNICATION_PORTS]",
       "COMPORT_6",0,&HOST_PORT))
    {
    AddError(WARNING007,0,0,7);
    }

  if (!GetProfileInt("[COMMUNICATION_PORTS]",
       "COMPORT_4",0,&GPS1_PORT))
    {
    AddError(WARNING007,0,0,7);
    }
  if (!GetProfileInt("[COMMUNICATION_PORTS]",
       "COMPORT_5",0,&GPS2_PORT))
    {
    AddError(WARNING007,0,0,8);
    }

  if (!GetProfileInt("[COMMUNICATION_PORTS]",
       "DebugPort",0,&DEBUG_PORT))
    {
    AddError(WARNING007,0,0,9);
    }
  
for (i=1; i<NBR_OF_PORTS+1;i++)
{
  if ((i==CON_PORT) ||  (i==BASEST_PORT) || (i==MONITOR_PORT) || (i==HOST_PORT) ||
        (i==GPS1_PORT) || (i==GPS2_PORT)  || (i==DEBUG_PORT) || (i==PLC_PORT))
   {
  
  	// com port initialization
     ActivePort[i]=TRUE;  // default
     if (i == 1)       
	    tmp_port=_com1;
     if (i == 2)
	    tmp_port=_com2;	   
     if (i == 3)
	    tmp_port=_com3;	  
     if (i == 4)	    
	    tmp_port=_com4;
		 if (i == 5)	    
	    tmp_port=_com5;  
		 if (i == 6)	    
	    tmp_port=_com6;  

		 if (i < 7)
	    {
	     if ((com_port[i]=comm_port_init(tmp_port)) == NULL)
         {
	        ActivePort[i]=FALSE;					
	        sprintf(tmpbuf,TX0098,i);
	        AddError(SEVERE_ERROR004,0,i,0);					
				  sprintf(tmpbuf,TX0098,i);				 
	       }
			  }

    if (i<7)
		{
	     strcpy(IniFileName,"comm");			 
			 IniFileName[4]=i+48;
			 IniFileName[5]=0;
	     strcat(IniFileName,".ini");	    

			if (comm_port_load_settings(com_port[i], IniFileName) == 0)
	      {
	       ActivePort[i]=FALSE;	   				 
			 	 sprintf(tmpbuf,TX0099,i);
	       AddError(SEVERE_ERROR005,0,i,0);	      
	      }
	   }

    if (i < 7)
	  {
	   if (!comm_port_install_handler(com_port[i]))
	    {
	      ActivePort[i]=FALSE;
	      //sprintf(tmpbuf,TX0098,i);
				sprintf(tmpbuf,TX0098,i);
	      AddError(SEVERE_ERROR004,0,i,1);					
	      //SendStr(tmpbuf,DEST,strlen(tmpbuf));
	      }
  	 }
  }
// place information to ErrStack for debugging purposes
  switch(i)
    {
    case 1:
	  AddError(INFO008,0,(long)ActivePort[i], 0);
	  break;
    case 2:
	  AddError(INFO009,0,(long)ActivePort[i], 0);
	  break;
    case 3:
	  AddError(INFO010,0,(long)ActivePort[i], 0);
  	break;
    case 4:
	  AddError(INFO011,0,(long)ActivePort[i],0 );		
	  break;
    default:
	  break;
    }
#ifdef COMM_TEST 
	  if (TRUE == ActivePort[i])
	   printf ("Comm port %d initialize - OK\n", i);
		else
     printf ("Comm port %d NOT initialize\n", i);
#endif
  } 
 */ 
 }

/********************************************************************

  Declaration: Read data from Rx buffer
  Call: ReceivedBytes=ReadRxData(PortNumber,RecvData)
  Input: int PortNumber (1-6), char *RecvData
  Returns: int ReceivedBytes
  08.11.2000 Initial coding

*********************************************************************/

int ReadRxData(int PortNumber, char * RecvData)
  {
  byte tmpchr;
  char MData[200];
  int c, j;
  int NbrOfReadBytes=0;

 // printf ("Enter to ReadRxData(). PortNumber=%d\n", PortNumber);

  // read a character, if no incomes, we got -1 and NbrOfReadBytes=0.
	// if something wes read, still "suck" it till no more characters.
	// results are in RecvData string.
 if (TRUE == ActivePort[PortNumber])
 {
	while ( (c = CPort[PortNumber]->ReadFromPort() ) != -1 )
    {
     *(RecvData++)=(char)c;
     NbrOfReadBytes++;
    }
 }
// check for capture

  if ( (CaptureComInput[PortNumber] && NbrOfReadBytes))
    {
    if (CaptureMode == 1) // Hex binary
      {
      for (j=0; j < NbrOfReadBytes; j++)
	      {
	       tmpchr=(byte)*(RecvData-NbrOfReadBytes+j);
	       sprintf(MData,"\\x%X",tmpchr);
			   SendStr(MData,origin,strlen(MData));
	      }
      }
    else
      {
       RecvData[NbrOfReadBytes]=0;
       SendStr( (RecvData-NbrOfReadBytes),origin,NbrOfReadBytes);
      }
    }
  //printf (" return NbrOfReadBytes=%d\n", NbrOfReadBytes);
  
	return NbrOfReadBytes;
  }

/********************************************************************

  Declaration: This is a wrapper function for Tdata
  Call: TxData(PortNumber, Data, NbrOfBytes)
  Input: int PortNumber (1-6),char * Data, int NbrOfBytes
  Returns: Number of bytes actually written. 0 if buffer full.
  29.12.2000 Initial coding.

*********************************************************************/

int TxData(int PortNumber, char * Data,int NbrOfBytes)

  {
  char MData[200];
  byte tmpchr;
  int i,j,Ret;
//printf ("sending message from port %d\n", PortNumber);
  if ( CaptureComOutput[PortNumber])
    {
    if (CaptureMode == 1)  // Hex binary
      {
      for (j=0; j < NbrOfBytes; j++)
        {
        tmpchr=(byte)*(Data+j);
        sprintf(MData,"\\x%x",tmpchr);
			  SendStr(MData,origin,strlen(MData));
        }
      }
    else  // raw binary
      {
 		  SendStr(Data,origin,NbrOfBytes);
      }
    }

 if (TRUE == ActivePort[PortNumber])
 {
  for (i=0; i<NbrOfBytes; i++)
  { 		
		Ret = CPort[PortNumber]->WriteToPort(*(Data++));
		if (!Ret)
    {
      return(i);
    }
  }
 }
 else 
 {
  printf ("ERROR! Comm port %d was not open!\n", PortNumber);
	i = 0;
 }
 return(i);
}



#ifdef RANDOM_MESSAGE  
/********************************************************************

  Savcor IT Oy/YS
  Declaration: Function creates message of randomised characters (litter)
	             and sends it to a COM port which is nCOM. 
							 REM: Test purposes only!!
	Call:  SendTestMes(nSize, nCOM)
  Input: size of message (int) and number of com-mport
  Returns: none
  05.05.2003 Initial coding / YS  
 
*********************************************************************/
void SendTestMes(int nSize, int nCOM)
{

  char  SendTx[nSize];
  int   y;
	long  StVal, Subst;
  int   RValue = FALSE;
  char  tmpbuff[30];
  int   random, flag; 
 
	srand((unsigned)time(NULL));


flag = 0;

for (y=0; y<nSize; y++)
{ 
  while(!flag)
		{
     random = rand() % 255;		
     if ((random >= 0) && (random <= 255))
      flag= 1;      
		}
	SendTx[y]= (unsigned char)random;		
	flag = 0;
}
 //printf("Start Time=%d\n", Get1msTimeMS());
 StVal = Get1msTimeMS();

 TxData(nCOM, SendTx, sizeof(SendTx));
do
{
  RValue = comm_port_out_empty(com_port[nCOM]);
} while (!RValue);

//printf("End Time=%d\n", Get1msTimeMS());
Subst = Get1msTimeMS() - StVal;

sprintf(tmpbuff, " Diff = %ld", Subst); 
TxData(nCOM, tmpbuff,strlen(tmpbuff));
//printf ("%s\n", tmpbuff);
}
#endif

/********************************************************************

  Declaration: 
	Call:  Send_0x20_Message (nSize, nCOM)
  Input: size of message (int) and number of com-mport
  Returns: none
  27.10.2006 Initial coding / YS  
  
	binary part:
	\0x23\0x1\0x1\0x1\0x1\0x1\0x0\0x0\0x1\0x1\0x1\0x1\0x72\0x9C\0x7E

*********************************************************************/
void Send_0x23_Message (int nSize, int nCOM)
{
  unsigned char  *IRISbuffer;   
  int nMsgSize = 14;
	unsigned char tmpchr;
	unsigned short calcCRC;
  unsigned char tmpBuf[2];

	t.TRACE ("nSize: 0x%X", nSize);
  t.TRACE (", %d\n", nSize);
  IRISbuffer = new unsigned char[15];

	IRISbuffer[0] =0x23;
	IRISbuffer[1] =0x2;
	IRISbuffer[2] =0x1;
	IRISbuffer[3] =0x2;
	IRISbuffer[4] =0x1;
	IRISbuffer[5] =0x2;
	IRISbuffer[6] =0x0;
	IRISbuffer[7] =0x0;
	IRISbuffer[8] = 0x1;
	IRISbuffer[9] = 0x1;
	IRISbuffer[10] =0x1;
	IRISbuffer[11] =0x1;
	
	calcCRC = NetworkServices::calcCRC(IRISbuffer, nMsgSize-2);	
	t.TRACE ("calculated CRC: 0x%X\n", calcCRC);
	memcpy ((void*)(tmpBuf),  (const void*)&calcCRC, sizeof(calcCRC) );

  IRISbuffer[12] =tmpBuf[1]; //0x35
	IRISbuffer[13] =tmpBuf[0]; //0xAC

	IRISbuffer[14] =0x7E;
 
 t.TRACE("Send_0x23_Message- "); 
 for (int j=0; j < nMsgSize+1; j++)
  {
   tmpchr=(unsigned char) IRISbuffer[j];
   t.TRACE("\\0x%X", tmpchr); 
	}
	t.TRACE("\n"); 

  TxData(nCOM, (char*)IRISbuffer, nMsgSize+1);

	delete [] IRISbuffer;
}
/********************************************************************

  Declaration: 
	Call:  Send_0x20_Message (nSize, nCOM)
  Input: size of message (int) and number of com-mport
  Returns: none
  27.10.2006 Initial coding / YS  
  
	binary part:
	\0x20\0x0\0x0\0xD\0x8E\0x0\0x0\0x0\0x17\0x0\0x0\0xD\0xC1\0x0
  \0x0\0xB\0xF\0x0\0x0\0xB\0x4D\0x0\0x0\0xA\0xDD\0x35\0xAC\0x7E

  \0x20
	\0x0\0x0\0xD\0x8E -
	\0x0\0x0\0x0\0x17 -
	\0x0\0x0\0xD\0xF3 -
	\0x0\0x0\0xB\0xF  -
	\0x0\0x0\0xB\0x4D -
	\0x0\0x0\0xA\0xA5 -
	\0xA5\0xEA        -CRC
	\0x7E             -End Flag
*********************************************************************/
void Send_0x20_Message (int nSize, int nCOM)
{
  unsigned char  *IRISbuffer;   
  int nMsgSize = 27;
	unsigned char tmpchr;
	unsigned short calcCRC;
  unsigned char tmpBuf[2];

	t.TRACE ("nSize: 0x%X", nSize);
  t.TRACE (", %d\n", nSize);
  IRISbuffer = new unsigned char[28];
  
	IRISbuffer[0] =0x20;
	
	IRISbuffer[1] =0x0;
	IRISbuffer[2] =0x0;	
	IRISbuffer[3] =0x1;
	IRISbuffer[4] =0x8E;
	
	IRISbuffer[5] =0x0;
	IRISbuffer[6] =0x0;	
	IRISbuffer[7] =0x0;
	//*(IRISbuffer+8) = 6;
	IRISbuffer[8] = nSize;// 0x05;
	
	IRISbuffer[9] = 0x0;
	IRISbuffer[10] =0x0;
	IRISbuffer[11] =0xD;
	IRISbuffer[12] =0xC1;	
	IRISbuffer[13] =0x0;
	IRISbuffer[14] =0x0;	
	IRISbuffer[15] =0xA;
	IRISbuffer[16] =0xA;

	IRISbuffer[17] =0x0;	
	IRISbuffer[18] =0x0;
	IRISbuffer[19] =0x2; // 0xB
	IRISbuffer[20] =0x4D;	
	IRISbuffer[21] =0x0; 
	IRISbuffer[22] =0x0;
	IRISbuffer[23] =0xA;
	IRISbuffer[24] =0xDD;
	
	calcCRC = NetworkServices::calcCRC(IRISbuffer, nMsgSize-2);	
	t.TRACE ("calculated CRC: 0x%X\n", calcCRC);
	memcpy ((void*)(tmpBuf),  (const void*)&calcCRC, sizeof(calcCRC) );

  IRISbuffer[25] =tmpBuf[1]; //0x35
	IRISbuffer[26] =tmpBuf[0]; //0xAC

	IRISbuffer[27] =0x7E;
 
 t.TRACE("Send_0x20_Message- "); 
 for (int j=0; j < nMsgSize+1; j++)
  {
   tmpchr=(unsigned char) IRISbuffer[j];
   t.TRACE("\\0x%X", tmpchr); 
	}
	t.TRACE("\n"); 

  TxData(nCOM, (char*)IRISbuffer, nMsgSize+1);

	delete [] IRISbuffer;
}
/********************************************************************

  Declaration: 
	Call:  Send_SET_AIR_VALVE_EN_Message (nSize, nCOM)
  Input: size of message (int) and number of com-mport
  Returns: none
  01.09.2004 Initial coding / YS  
 
*********************************************************************/
void Send_TEST_Message (int nSize, int nCOM)
{
  unsigned char  *IRISbuffer;   
  int nMsgSize = 12;
	unsigned char tmpchr;

  IRISbuffer = new unsigned char[15];

	IRISbuffer[0] =0x1E;
	IRISbuffer[1] =0x8F;
	IRISbuffer[2] =0x12;
	IRISbuffer[3] =0x36;
	IRISbuffer[4] =0x93;
	IRISbuffer[5] =0x10;
	IRISbuffer[6] =0x4;
	IRISbuffer[7] =0x41;
	IRISbuffer[8] =0xCC;
	IRISbuffer[9] =0xE;
	IRISbuffer[10]=0xF;
	IRISbuffer[11]=0x7E;
	//IRISbuffer[0]=0x
	//IRISbuffer[0]=0x
  
 t.TRACE("Send- "); 
 for (int j=0; j < nMsgSize; j++)
  {
   tmpchr=(unsigned char) IRISbuffer[j];
   t.TRACE("\\0x%X", tmpchr); 
	}
	t.TRACE("\n"); 

  TxData(nCOM, (char*)IRISbuffer, nMsgSize);

	delete [] IRISbuffer;
}

/********************************************************************

  Declaration: 
	Call:  Send_1F_Message (nSize, nCOM)
  Input: num of message (int) and number of com-mport
  Returns: none
  01.09.2004 Initial coding / YS  
 
*********************************************************************/
void Send_1F_Message (int nNum, int nCOM)
{
  unsigned char  *IRISbuffer;   
  int nMsgSize = 5;
	unsigned char tmpchr;
  unsigned short calcCRC;
  unsigned char tmpBuf[2];

  IRISbuffer = new unsigned char[nMsgSize];
    
	// 0x1E = 30

	IRISbuffer[0]=0x1F;
	IRISbuffer[1]=nNum;
  
	calcCRC = NetworkServices::calcCRC(IRISbuffer, 2);
	
	//t.TRACE ("calculated CRC: 0x%X\n", calcCRC);
	memcpy ((void*)(tmpBuf),  (const void*)&calcCRC, sizeof(calcCRC) );
	
	IRISbuffer[2]=tmpBuf[1];
	IRISbuffer[3]=tmpBuf[0];
		
	IRISbuffer[4]=0x7E;
		
 t.TRACE("Send- "); 
 for (int j=0; j < nMsgSize; j++)
  {
   tmpchr=(unsigned char) IRISbuffer[j];
   t.TRACE("\\0x%X", tmpchr); 
	}
	t.TRACE("\n"); 

  TxData(nCOM, (char*)IRISbuffer, nMsgSize);

	delete [] IRISbuffer;
}


/********************************************************************

  Declaration: 
	Call:  Send_EMPTY_Message (nSize, nCOM)
  Input: message number (int) and number of com-mport
  Returns: none
  01.09.2004 Initial coding / YS  
 
*********************************************************************/
void Send_EMPTY_Message (int nNumber, int nCOM)
{
  unsigned char  *IRISbuffer;   
  int nMsgSize = 6;
	unsigned char tmpchr;
  unsigned short calcCRC;
  unsigned char tmpBuf[2];

  IRISbuffer = new unsigned char[nMsgSize];
  
	IRISbuffer[0]=nNumber;
	IRISbuffer[1]=0x0;
	IRISbuffer[2]=0x0;
	// IRISbuffer[5]=0x7E;

	calcCRC = NetworkServices::calcCRC(IRISbuffer, 3);
	
	// t.TRACE ("calculated CRC: 0x%X\n", calcCRC);
	memcpy ((void*)(tmpBuf),  (const void*)&calcCRC, sizeof(calcCRC) );
	IRISbuffer[3]=tmpBuf[1];
	IRISbuffer[4]=tmpBuf[0];
	
	// memcpy((void *)&BD_Header[GPSNbr], (const void*)RecvData[GPSNbr], sizeof(BD_HEADER));
	//IRISbuffer[0]=0x
  //\0x2B\0x0\0x0\0x8\0x70\0x7E
	//IRISbuffer[0]=0x
  
  IRISbuffer[5]=0x7E;

 t.TRACE("Send- "); 
 for (int j=0; j < nMsgSize; j++)
  {
   tmpchr=(unsigned char) IRISbuffer[j];
   t.TRACE("\\0x%X", tmpchr); 
	}
	t.TRACE("\n"); 

  TxData(nCOM, (char*)IRISbuffer, nMsgSize);

	delete [] IRISbuffer;
}


/********************************************************************

  Declaration: Function creates message "log versiona" and sending 
               it to a COM port connected to a GPS card. Testing purpose 
               only.
	Call:  SendGPSTESTMessage (nSize, nCOM)
  Input: size of message (int) and number of com-mport
  Returns: none
  01.09.2004 Initial coding / YS  
 
*********************************************************************/
void SendGPSTESTMessage(int nSize, int nCOM)
{
   char  SendTx[15];   
   int   RValue = FALSE; 
   
 sprintf(SendTx, "%s%c", "log versiona", 0x0D);
 TxData(nCOM, SendTx, sizeof(SendTx));
/*
do
{
  RValue = comm_port_out_empty(com_port[nCOM]);
} while (!RValue);
*/
}


/********************************************************************

  Declaration: Function creates message of randomised characters (litter)
	             and sends it to a COM port which is nCOM. 
							 REM: Test purposes only!!
	Call:  SendTestMes(nSize, nCOM)
  Input: size of message (int) and number of com-mport
  Returns: none
  05.05.2003 Initial coding / YS  
 
*********************************************************************/
void SendZEROMessage(int nSize, int nCOM)
{
   //char  SendTx[15];   
   int   RValue = FALSE; 
/*
  int   random, flag; 
  char  tmpbuff[30];
  int   y;
	long  StVal, Subst;


	flag = 0;
  random = 0;

	srand((unsigned)time(NULL)); 

for (y=0; y<nSize; y++)
{ 
  while(!flag)
		{
     random = rand() % 255;		
     if ((random >= 0) && (random <= 255))
      flag= 1;      
		}
	SendTx[y]= (unsigned char)random;		
	flag = 0;
}

	sprintf (tmpBuffPXYZ, "%.2f", PsrXYZ.Z_Coord);
	strcat (SrStrPXYZ, tmpBuffPXYZ);
*/

 // SendTx[0]= 0x23;
//#ifdef COMM-1-TEST
// sprintf (SendTx, "COMM-%d-TEST; ", nCOM); 
// TxData(nCOM, SendTx, sizeof(SendTx));
//#endif

/*do
{
  RValue = comm_port_out_empty(com_port[nCOM]);
} while (!RValue);
*/
}

/*******************************************************************************
** Author:    Bill Theisen
** Purpose:   Searches the string for the specified character - ignores	NULL chars
**            in string.
** Comments:  Note, this method searchs entire string for character rather than stopping
**       	  at NULL.
**  Parameter(s):   char *string - string to search
**					int c - value to search for
**					int size - string size
**
**  Return type:    char * - pointer to char if found, otherwise NULL 
*******************************************************************************/
char * FindChr( char *searchString, int c, unsigned long size )
{
  // printf ("FindChr income. size: %d, searchString: %s\n", size, searchString);
	if( searchString != NULL )
	{
		while( size > 0 )
		{
			if( *searchString == c )
			{
			 //printf ("FindChr: Char 0x%X found on place %d\n", c, size);
			 return searchString;
			}
			searchString++;
			size--;
		}
	}
    return NULL;
}

#if 0
/********************************************************************

  Declaration: This is the thread that reads serial data, parses IRIS
	             packets and transfers them to the specified 
							 receiving method.
	Call:  
  Input: 
  Returns: 
  16.10.2006 Initial coding / YS  
 
*********************************************************************/
// unsigned int WINAPI DOIrisSerialPort::ReadThread( LPVOID pArg )
unsigned int DOIrisReadThread(IRIS_Node *pINode, char *cBuffer, unsigned long num)
{
    //unsigned long fdwCommMask;
     
    unsigned long CharsInBuffer = 0;
    unsigned long NonPacketCharsInBuffer;
    unsigned long packetlength;
    unsigned char tmpchr;
	  char * pEndChar;
		// unsigned long num;

    //LPSerial pCaller = reinterpret_cast<LPSerial>(pArg);
	  //DO_ASSERT( pCaller != NULL );
    //pCaller->m_bReadThreadIsRunning = TRUE;
    /*
    if ( pCaller->m_msgReceiver )
    {
        pCaller->m_msgReceiver->InitializeThread();
    }
    */
    // Enable logging from this thread via pCaller->m_pRnDLog.
    
	//HRESULT hRes = E_FAIL;
    //pCaller->m_pRnDLog->AddThread( hRes );   
    //DO_ASSERT( SUCCEEDED(hRes) );
 //printf ("DOIrisReadThread income. length=%d\n", num);
	// Setup the input and packet buffers 
    //char *cBuffer = new char[300];// [pCaller->m_iInBufferLength];
    //DO_ASSERT( cBuffer != NULL );
    char *cPacketBuffer = new char[300];//[pCaller->m_iPacketBufferLength];
    //DO_ASSERT( cPacketBuffer != NULL );
    /*
    if( !SetCommMask( pCaller->m_hPort, EV_RXCHAR | EXIT_EVENT ) )
		{
      pCaller->m_pRnDLog->LogRnDEvent( IDS_IRISCOMMON_SETCOMMMASK_FAILED );
    }    
    
		// Main loop of read thread.
    while( !pCaller->m_bStopReadThread )
    {
        if( !WaitCommEvent(pCaller->m_hPort, &fdwCommMask, 0))
        {
            //pCaller->m_pRnDLog->LogRnDEvent( IDS_IRISCOMMON_WAITCOMMEVENT_FAILED, 
            //                                 static_cast<int>(GetLastError()) );
            break;	//	Get out of read thread while loop 
        }
        
      // Reset the comm Mask.
       if( !SetCommMask(pCaller->m_hPort, EV_RXCHAR | EXIT_EVENT))
				{
            //pCaller->m_pRnDLog->LogRnDEvent( IDS_IRISCOMMON_SETCOMMMASK_FAILED,
            //                                 static_cast<int>(GetLastError()));
        }
    
        if( fdwCommMask & EV_RXCHAR )
        {
            unsigned long num;
#ifdef _WIN32_WCE
         // Read all bytes received into cBuffer.
			  ReadFile(pCaller->m_hPort, &cBuffer[CharsInBuffer], pCaller->m_iInBufferLength-CharsInBuffer, &num, 0);
#else
        ReadFile(pCaller->m_hPort, &cBuffer[CharsInBuffer], pCaller->m_iInBufferLength-CharsInBuffer, &num, &(pCaller->m_overlapped));
#endif // _WIN32_WCE
				*/
            CharsInBuffer += num;
            //printf ("CharsInBuffer = %d\n", CharsInBuffer);
            // Check for a packet in the buffer
            while( CharsInBuffer && (pEndChar = FindChr( cBuffer, IRIS_PACKET_END_FLAG, CharsInBuffer )) != NULL )
            {	
							packetlength = static_cast<unsigned long>((pEndChar - cBuffer) + 1);  // Includes IRIS_PACKET_END_FLAG char
              //printf ("packetlength=%d, pEndChar=%d\n", packetlength, pEndChar); 
                // Make sure IRIS_PACKET_END_FLAG is in new message area of buffer
                if ( packetlength <= CharsInBuffer) //&& packetlength <= pCaller->m_iPacketBufferLength )
                {
                  // Move packet to buffer and send
                  memcpy( cPacketBuffer, cBuffer, packetlength);	// PC-Lint warning 688 expected
								  t.TRACE("cPacketBuffer: "); 
									for (int j=0; j < packetlength; j++)
									{
										tmpchr=(unsigned char) cPacketBuffer[j];
										t.TRACE("\\0x%X", tmpchr);
									}
									t.TRACE("\n"); 
		    	        // pCaller->PktCallRelay( cPacketBuffer, packetlength );
									pINode->receivePacket( cPacketBuffer, packetlength ); 

                }

                // Move remaining chars in buffer to beginning of buffer and adjust char counts
                NonPacketCharsInBuffer = CharsInBuffer - packetlength;

                if( NonPacketCharsInBuffer > 0 )
								{
									// PC-Lint warning 688 expected
                  memcpy( cBuffer, &cBuffer[CharsInBuffer-NonPacketCharsInBuffer], NonPacketCharsInBuffer);
                }
                else
                {
                  NonPacketCharsInBuffer = 0;
                }
				      CharsInBuffer = NonPacketCharsInBuffer; 
            }

			// Handle the case were the buffer is full but no packet is found
            if( CharsInBuffer >=  300)//pCaller->m_iInBufferLength )
            {
              CharsInBuffer = 0;
              //pCaller->m_pRnDLog->LogRnDEvent( IDS_IRISCOMMON_BUFFER_OVERFLOW );
            }
 //       } // if(?)
        
        // Clear buffers to prevent problem when exiting thread
				/*
        if( fdwCommMask & EXIT_EVENT )
				{
            PurgeComm(pCaller->m_hPort, PURGE_RXCLEAR | PURGE_TXCLEAR | 
                                        PURGE_RXABORT | PURGE_TXABORT );
        }
				*/
 //   }    //while

	//delete [] cBuffer;
	delete [] cPacketBuffer;

    //pCaller->m_pRnDLog->RemoveThread();
    /*
    if ( pCaller->m_msgReceiver )
    {
        pCaller->m_msgReceiver->ShutdownThread();
    }

    pCaller->m_bReadThreadIsRunning = FALSE;
    */

    return 0;
}
#endif
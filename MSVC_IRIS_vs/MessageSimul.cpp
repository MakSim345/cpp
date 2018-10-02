#include "gen.h"
#include "MessageSimul.h"
#include "Message.h"
//#include "utils.h"
#include "NetworkServices.h"
#include "comminc.h"
#include "VcbTestMessageHeaders.h"

extern CTRACE t;

/********************************************************************

  Declaration: 
	Call:  Send_0x23_Message (nSize, nCOM)
  Input: size of message (int) and number of com-mport
  Returns: none
  27.10.2006 Initial coding / YS  
  
	binary part:
	\0x23\0x1\0x1\0x1\0x1\0x1\0x0\0x0\0x1\0x1\0x1\0x1\0x72\0x9C\0x7E

*********************************************************************/
void Send_0x23_Message (int nSize, int nCOM)
{
  unsigned char  *IRISbuffer;   
  const int nMsgSize = 15;
	unsigned char tmpchr;
	unsigned short calcCRC;
  unsigned char tmpBuf[2];

	t.TRACE ("nSize: 0x%X", nSize);
  t.TRACE (", %d\n", nSize);
  IRISbuffer = new unsigned char[nMsgSize];

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
	
	calcCRC = NetworkServices::calcCRC(IRISbuffer, nMsgSize-3);	
	t.TRACE ("calculated CRC: 0x%X\n", calcCRC);
	memcpy ((void*)(tmpBuf),  (const void*)&calcCRC, sizeof(calcCRC) );

  IRISbuffer[12] =tmpBuf[1]; //0x35
	IRISbuffer[13] =tmpBuf[0]; //0xAC

	IRISbuffer[14] =0x7E;
 
 t.TRACE("Send_0x23_Message- "); 
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
	Call:  Send_0x24_Message (nSize, nCOM)
  Input: size of message (int) and number of com-mport
  Returns: none
  10.11.2006 Initial coding / YS  
  
	binary part:
	
	\0x24\0x4E\0x6F\0x6E\0x65\0x00\0x78\0x70\0x20\0x46
	\0x6C\0x6F\0x77\0x20\0x53\0x65\0x6E\0x73\0x6F\0x72
	\0x20\0x43\0x61\0x6C\0x20\0x50\0x61\0x73\0x73\0x00
	\0x00\0x00\0x00\0x00\0x00\0x00\0x00\0x00\0x00\0x00
	\0x00\0x18\0x07\0xD0\0x56\0xE7\0x7E

*********************************************************************/
void Send_0x24_Message (int nSize, int nCOM)
{
  unsigned char  *IRISbuffer;   
  const int nMsgSize = 47;
	unsigned char tmpchr;
	unsigned short calcCRC;
  unsigned char tmpBuf[2];

	t.TRACE ("nSize: 0x%X", nSize);
  t.TRACE (", %d\n", nSize);
  IRISbuffer = new unsigned char[nMsgSize];
  // Message ID:
	IRISbuffer[0] = 0x24;
	IRISbuffer[1] = 0x4E;
	IRISbuffer[2] = 0x6F;	
	IRISbuffer[3] = 0x6E;
	IRISbuffer[4] = 0x65;
	IRISbuffer[5] = 0x00;
	IRISbuffer[6] = 0x78;	
	IRISbuffer[7] = 0x70;
	IRISbuffer[8] = 0x20;
	IRISbuffer[9] = 0x46;
	IRISbuffer[10] =0x6C;
	IRISbuffer[11] =0x6F;
	IRISbuffer[12] =0x77;
	IRISbuffer[13] =0x20;
	IRISbuffer[14] =0x53;	
	IRISbuffer[15] =0x65;
	IRISbuffer[16] =0x6E;
	IRISbuffer[17] =0x73;	
	IRISbuffer[18] =0x6F;
	IRISbuffer[19] =0x72;
	IRISbuffer[20] =0x20;
	IRISbuffer[21] =0x43; 
	IRISbuffer[22] =0x61;
	IRISbuffer[23] =0x6C;
	IRISbuffer[24] =0x20;
	IRISbuffer[25] =0x50;
	IRISbuffer[26] =0x61;
	IRISbuffer[27] =0x73;
	IRISbuffer[28] =0x73;
	IRISbuffer[29] =0x00;
	IRISbuffer[30] =0x00;
	IRISbuffer[31] =0x00;
	IRISbuffer[32] =0x00;
	IRISbuffer[33] =0x00;
	IRISbuffer[34] =0x00;
	IRISbuffer[35] =0x00;
	IRISbuffer[36] =0x00;
	IRISbuffer[37] =0x00;
	IRISbuffer[38] =0x00;
	IRISbuffer[39] =0x00;
	IRISbuffer[40] =0x00;
	IRISbuffer[41] =0x18;
	IRISbuffer[42] =0x07;
	IRISbuffer[43] =0xD0;
	IRISbuffer[44] =0x00;
	IRISbuffer[45] =0x00;
		
	calcCRC = NetworkServices::calcCRC(IRISbuffer, nMsgSize-3);	
	t.TRACE ("calculated CRC: 0x%X\n", calcCRC);
	memcpy ((void*)(tmpBuf),  (const void*)&calcCRC, sizeof(calcCRC) );

  IRISbuffer[44] =tmpBuf[1]; 
	IRISbuffer[45] =tmpBuf[0]; 

	IRISbuffer[46] =0x7E;
 
 t.TRACE("Send_0x24_Message- "); 
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
	Call:  Send_0x24_Message_I (nSize, nCOM)
  Input: size of message (int) and number of com-mport
  Returns: none
  10.11.2006 Initial coding / YS  
  
*********************************************************************/
void Send_0x20_Message_I (int nSize, int nCOM)
{
  unsigned char  *IRISbuffer; 
  const int nMsgSize = 28;
	unsigned char tmpchr;
  IRISbuffer = new unsigned char[nMsgSize];
  VcbTest_SensorInfo *Vcb_SensorInfo = new VcbTest_SensorInfo();
  
	Vcb_SensorInfo->TotalFlow = 11+nSize;
  Vcb_SensorInfo->OxygenFlow= 12;
  Vcb_SensorInfo->AirFlow = 13;
	Vcb_SensorInfo->TotalCurrentTemp= 567;
  Vcb_SensorInfo->OxygenCurrentTemp= 235;
  Vcb_SensorInfo->AirCurrentTemp= 145;
	
	Vcb_SensorInfo->serialize(IRISbuffer);
  
	IRISbuffer[27] =0x7E; // this is wrong, because we should use something like "stuff message"

  t.TRACE("Send_0x20_MessageI - ");
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
	Call:  Send_0x20_Message (nSize, nCOM)
  Input: size of message (int) and number of com-mport
  Returns: none
  27.10.2006 Initial coding / YS  
  
	binary part:
	\0x20\0x0\0x0\0xD\0x8E\0x0\0x0\0x0\0x17\0x0\0x0\0xD\0xC1\0x0
  \0x0\0xB\0xF\0x0\0x0\0xB\0x4D\0x0\0x0\0xA\0xDD\0x35\0xAC\0x7E

*********************************************************************/
void Send_0x20_Message (int nSize, int nCOM)
{
  unsigned char  *IRISbuffer;   
  const int nMsgSize = 28;
	unsigned char tmpchr;
	unsigned short calcCRC;
  unsigned char tmpBuf[2];

	t.TRACE ("nSize: 0x%X", nSize);
  t.TRACE (", %d\n", nSize);
  IRISbuffer = new unsigned char[nMsgSize];
  // Message ID:
	IRISbuffer[0] =0x20;

	// Flow ml/min - Total:
	IRISbuffer[1] =0x0;
	IRISbuffer[2] =0x0;	
	IRISbuffer[3] =0x0;
	IRISbuffer[4] =0x8E;
	// Flow ml/min - Oxygen:
	IRISbuffer[5] =0x0;
	IRISbuffer[6] =0x0;	
	IRISbuffer[7] =0x0;
	//*(IRISbuffer+8) = 6;
	IRISbuffer[8] = nSize;// 0x05;

// Flow ml/min - Air:	
	IRISbuffer[9] = 0x0;
	IRISbuffer[10] =0x0;
	IRISbuffer[11] =0x0;
	IRISbuffer[12] =0xC1;

//Temperature - Total:	
	IRISbuffer[13] =0x0;
	IRISbuffer[14] =0x0;	
	IRISbuffer[15] =nSize;
	IRISbuffer[16] =nSize; //0x0;

//Temperature - Oxygen:	
	IRISbuffer[17] =0x0;	
	IRISbuffer[18] =0x0;
	IRISbuffer[19] =0x0; // 0xB
	IRISbuffer[20] =0x4D;

//Temperature - air:		
	IRISbuffer[21] =0x0; 
	IRISbuffer[22] =0x0;
	IRISbuffer[23] =0x0;
	IRISbuffer[24] =0x4D;
	
	calcCRC = NetworkServices::calcCRC(IRISbuffer, nMsgSize-3);	
	t.TRACE ("calculated CRC: 0x%X\n", calcCRC);
	memcpy ((void*)(tmpBuf),  (const void*)&calcCRC, sizeof(calcCRC) );

  IRISbuffer[25] =tmpBuf[1]; //0x35
	IRISbuffer[26] =tmpBuf[0]; //0xAC

	IRISbuffer[27] =0x7E;
 
 t.TRACE("Send_0x20_Message- "); 
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
	Call:  SendRequestMessage (nSize, nCOM)
  Input: num of message (int) and number of com-mport
  Returns: none
  01.09.2004 Initial coding / YS  
 
*********************************************************************/
void SendRequestMessage (int nNum, int nCOM)
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

/*********************************************************************

  cominc.h
	communication incapsulate
  12.10.2006 Initial coding

**********************************************************************/
#ifndef _COMM_IF_H_
#define _COMM_IF_H_	
	
void ResetSerialInterrupts();
void InitSerialPorts(int);
void RemoveSerialPortFromPoll();
int TxData(int , char * ,int );
int ReadRxData(int , char * );
void SendTestMes(int nSize, int nCOM);
void SendZEROMessage(int nSize, int nCOM);
void SendGPSTESTMessage (int nSize, int nCOM);
void Send_SET_AIR_VALVE_EN_Message (int nSize, int nCOM);

#endif // _COMINC_H_
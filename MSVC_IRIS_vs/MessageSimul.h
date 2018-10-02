/*********************************************************************

  MessageSimul.h
	IRIS EVE messages binary simulator
  12.10.2006 Initial coding

**********************************************************************/
#ifndef _MESSAGESIMUL_H_
#define _MESSAGESIMUL_H_	
	
void SendRequestMessage (int nNum, int nCOM);
void Send_0x20_Message (int nSize, int nCOM);
void Send_0x23_Message (int nSize, int nCOM);
void Send_0x24_Message (int nSize, int nCOM);

void Send_0x20_Message_I(int nSize, int nCOM);

#endif // _MESSAGESIMUL_H_
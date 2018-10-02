#ifndef RINGBUF_H
#define RINGBUF_H

#include "gen.h"	

typedef struct
{	
  char Msg[500]; // for messages.
  int MsgLen;
  int MobId;
  int MsgCntr;
  int MsgId;
  int ReSendCntr;
  int FreeCell;  	  

} VCMsgSent1;  


typedef struct
{  
  int FreeCell;
  int MsgId;  
  int Param;
  
  // reserved:
  int ReSendCntr;
  int MsgCntr;

} VCMsgSent; 



//-----------------------------------------
class DynBuff
{
 public:
 // Constructor
  DynBuff();
  DynBuff(int);
  ~DynBuff();

  int isEmpty();
  int getMsgId(int);
  int getMsgSize(int);
  int getAllCellCtr(); // Msg's array returns
  int getCellCtr(void);
  int getHead();
  int getTail();

  int  getMsgFromStore(int*, int*);
  void putMsgToStore(int, int);
  
  int readMsgFromStore(int);
  
  int getCellBusy(int); // returns TRUE if cell free; FALSE if it's busy. Obvious..
  
  void PrintDump(void);

 protected:
	 
  // VCMsgSent MsgSent[30];
  VCMsgSent *MsgSent;
  int m_MsgExistFlag; // something to send

  int m_IntCtr;
  int m_Tail;
  int m_Head;
  int m_CellCntr;  
  int m_ArraySize;
  int m_nOverflowFlag;

  void ResetCell(int);  
  void decCellCtr(void);
  void incCellCtr(void);
  void setMsgExistFlag(int);
  
};

#endif // MSGBUF_H
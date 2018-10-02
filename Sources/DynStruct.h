typedef struct
{	
  char Msg[500]; // for messages.
  int MsgLen;
  int MobId;
  int MsgCntr;
  int MsgNumber;
  int ReSendCntr;
  int FreeCell;
  
  	  
} PCCMsgSent;  

//-----------------------------------------
class DynBuff
{
 public:
 // Constructor
  DynBuff();

  int GetGlobalFlag();
  int Get_MsgNbr(int Nbr);
  int Get_MsgSize(int Nbr);
  int Get_MobId(int Nbr);
  int Get_CellCtr(); // Msg's array returns

  int EraseMsgFromStore(char * Msg);
  int GetMsgFromStore(char * Msg, int Nbr); // returns a message size 
  
  int GetCellBusy(int Nbr); // returns TRUE if cell free; FALSE if it's busy. Obvious..
  
	int HandleMsgCtr(int);
  void PutMsgToStore(char * Msg, int MsgSize);
  void SetGlobalFlag(int Value);	

 public:
  ~DynBuff();

 protected:
	 
  PCCMsgSent MsgSent[30];
  
  int m_GlobFlag; // something to send

  int m_IntCtr;
  int m_Current;
  int m_CellCntr;
	int m_ReSendNum; // how many times message will be re-send
	int m_ArraySize;

  void ResetCell(int);
  void SetGlobalFlag();
  int Get_Free();

};

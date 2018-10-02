#ifdef IPA
typedef struct
{	
  int Ctr;
  int	Status;	
} PPMsgSent;  

class SetPPMsgInfo
{
 public:
 // Constructor
  SetPPMsgInfo();

  int  Get_Free();  
  void Set_True(int Nbr);
  void Set_False(int Nbr);  
  int Get_Status(int Nbr);
  int Get_Counter(int Nbr);
  
	int  Get_NoTOSConnectCtr(int Nbr);	
	void Inc_NoTOSConnectCtr(int Nbr);
	void Reset_NoTOSConnectCtr(int Nbr);

	int  Get_ReSendingCounter(int Nbr);	
	void Inc_ReSendingCounter(int Nbr);
	void Reset_ReSendingCounter(int Nbr);

 public:
  ~SetPPMsgInfo();

 protected:
	 
  PPMsgSent PickPlaceMsgSent[10];
  int m_IntCtr;
  int m_Current; 
	int m_ArraySize;
  int m_NoTOSConnectCtr[10];
  int m_ReSendingCounter[10];

	void ResetCell(int);
};

#endif // IPA
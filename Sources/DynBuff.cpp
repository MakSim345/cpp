#ifdef IPA
typedef struct
{	
  int Ctr;
  int Status;
  // not really OOP ideology: m_Msg can be obtain directly.
  char m_Msg[50]; // for messages.
  	  
} PPMsgSent;  

class DynBuff
{
 public:
 // Constructor
  DynBuff();

  int Get_Free();  
  int GetGlobalFlag();
  
  void Set_True(int Nbr);
  void Set_False(int Nbr);  
  int Get_Status(int Nbr);
  int Get_Counter(int Nbr);
  
  int  Get_NoConnnectCtr(int Nbr);	
  void Inc_NoConnnectCtr(int Nbr);
  void Reset_NoConnnectCtr(int Nbr);
  
  int  Get_ReSendCtr(int Nbr);	
  void Inc_ReSendCtr(int Nbr);
  void Reset_ReSendCtr(int Nbr);

 public:
  ~DynBuff();

 protected:
	 
  PPMsgSent MsgSent[10];
  int m_globFlag;
  int m_IntCtr;
  int m_Current; 
  int m_ArraySize;
  int m_NoConnnectCtr[10];
  int m_ReSendCtr[10];

  void ResetCell(int);
};

#endif // IPA


#ifdef IPA
// ----DynBuff--FUNCTIONS:
	
DynBuff::DynBuff()
{  
 m_Current   = 0;
 m_ArraySize = 10; 
 for (m_IntCtr=0; m_IntCtr < m_ArraySize; m_IntCtr++)
    ResetCell(m_IntCtr);  
}

// Destructor:
DynBuff::~DynBuff()
{
 return;
}

void DynBuff::ResetCell(int Nbr)
{
  MsgSent[Nbr].Ctr = -1;
  MsgSent[Nbr].Status = FALSE;
  // MsgSent[Nbr].Msg = NULL
}

int  DynBuff::Get_Free()
{
 // return number of free cell for saving next msg there.
 for (m_IntCtr=0; m_IntCtr < m_ArraySize; m_IntCtr++)
 {     
  if (!MsgSent[m_IntCtr].Status)
  {
   m_Current = m_IntCtr;
	 // TRACE ("Get_Free returns %d.\n", m_Current);
   return m_Current;
  }
 }	     
 // TRACE ("Get_Free returns 0, because no free cells.\n");
 m_Current = 0;		 
 return 0; // in case, there are no any free cells...
}

void  DynBuff::Set_True(int Nbr) 
{
 // m_Current is already set! See above - Get_Free();
 MsgSent[m_Current].Ctr = Nbr;
 MsgSent[m_Current].Status = TRUE;
} 
  
void  DynBuff::Set_False(int Nbr)
{
	// Beware: "Nbr" here means value of the Counter in the 
	// message was re-sended, not the number of element of array.
 for (m_IntCtr=0; m_IntCtr < m_ArraySize; m_IntCtr++)
 {
  if(MsgSent[m_IntCtr].Ctr == Nbr)
		{     
		 Reset_ReSendCtr(m_IntCtr);
		 Reset_NoConnnectCtr (m_IntCtr);
		 ResetCell(m_IntCtr);  
		}
 }
}	
 
int  DynBuff::Get_Status(int Nbr) 
{   
  return MsgSent[Nbr].Status;	 
}

int  DynBuff::Get_Counter(int Nbr) 
{   
  return MsgSent[Nbr].Ctr;
}
// set of NoConnnectCtr handling functions:
int  DynBuff::Get_NoConnnectCtr(int Nbr)
{   
  return m_NoConnnectCtr[Nbr];
}
void DynBuff::Inc_NoConnnectCtr(int Nbr)
{   
  m_NoConnnectCtr[Nbr]++;
}
void  DynBuff::Reset_NoConnnectCtr(int Nbr)
{   
  m_NoConnnectCtr[Nbr]=0;
}


// set of ReSendCtr handling functions:
int  DynBuff::Get_ReSendCtr(int Nbr)
{   
  return m_ReSendCtr[Nbr];
}
void DynBuff::Inc_ReSendCtr(int Nbr)
{   
  m_ReSendCtr[Nbr]++;
}
void  DynBuff::Reset_ReSendCtr(int Nbr)
{   
  m_ReSendCtr[Nbr]=0;
}


// End of class implementation.
#endif // IPA	
#ifdef IPA
// ----SetPPMsgInfo--FUNCTIONS:
	
SetPPMsgInfo::SetPPMsgInfo()
{  
 m_Current   = 0;
 m_ArraySize = 10; 
 for (m_IntCtr=0; m_IntCtr < m_ArraySize; m_IntCtr++)
    ResetCell(m_IntCtr);  
}

// Destructor:
SetPPMsgInfo::~SetPPMsgInfo()
{
 return;
}

void SetPPMsgInfo::ResetCell(int Nbr)
{
  PickPlaceMsgSent[Nbr].Ctr = -1;
  PickPlaceMsgSent[Nbr].Status = FALSE;
}

int  SetPPMsgInfo::Get_Free()
{
 // return number of free cell for saving next msg there.
 for (m_IntCtr=0; m_IntCtr < m_ArraySize; m_IntCtr++)
 {     
  if (!PickPlaceMsgSent[m_IntCtr].Status)
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

void  SetPPMsgInfo::Set_True(int Nbr) 
{
 // m_Current is already set! See above - Get_Free();
 PickPlaceMsgSent[m_Current].Ctr = Nbr;
 PickPlaceMsgSent[m_Current].Status = TRUE;
} 
  
void  SetPPMsgInfo::Set_False(int Nbr)
{
	// Beware: "Nbr" here means value of the Counter in the 
	// message was re-sended, not the number of element of array.
 for (m_IntCtr=0; m_IntCtr < m_ArraySize; m_IntCtr++)
 {
  if(PickPlaceMsgSent[m_IntCtr].Ctr == Nbr)
		{     
		 Reset_ReSendingCounter(m_IntCtr);
		 Reset_NoTOSConnectCtr (m_IntCtr);
		 ResetCell(m_IntCtr);  
		}
 }
}	
 
int  SetPPMsgInfo::Get_Status(int Nbr) 
{   
  return PickPlaceMsgSent[Nbr].Status;	 
}

int  SetPPMsgInfo::Get_Counter(int Nbr) 
{   
  return PickPlaceMsgSent[Nbr].Ctr;
}
// set of NoTOSConnectCtr handling functions:
int  SetPPMsgInfo::Get_NoTOSConnectCtr(int Nbr)
{   
  return m_NoTOSConnectCtr[Nbr];
}
void SetPPMsgInfo::Inc_NoTOSConnectCtr(int Nbr)
{   
  m_NoTOSConnectCtr[Nbr]++;
}
void  SetPPMsgInfo::Reset_NoTOSConnectCtr(int Nbr)
{   
  m_NoTOSConnectCtr[Nbr]=0;
}


// set of ReSendingCounter handling functions:
int  SetPPMsgInfo::Get_ReSendingCounter(int Nbr)
{   
  return m_ReSendingCounter[Nbr];
}
void SetPPMsgInfo::Inc_ReSendingCounter(int Nbr)
{   
  m_ReSendingCounter[Nbr]++;
}
void  SetPPMsgInfo::Reset_ReSendingCounter(int Nbr)
{   
  m_ReSendingCounter[Nbr]=0;
}


// End of class implementation.
#endif // IPA	
// ----DynBuff--FUNCTIONS:


// Constructor:	
DynBuff::DynBuff()
{
 m_ArraySize = 30;
 m_CellCntr = 0;
 m_Current = -1; 
 m_ReSendNum = 5;
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
  MsgSent[Nbr].FreeCell      =  1;
  MsgSent[Nbr].MobId         = -1;
  MsgSent[Nbr].MsgNumber     = -1;
  MsgSent[Nbr].MsgCntr       = -1;
  MsgSent[Nbr].MsgLen        = -1;
  MsgSent[Nbr].ReSendCntr    = -1;

	// Check if there any cell are in use. 
	// If not - reset global flag: nothing to send anymore.
	m_CellCntr--;  
	if (0 == m_CellCntr)
		SetGlobalFlag(0);
}

int  DynBuff::Get_Free()
{
 // return number of free cell for saving next msg there.
 for (m_IntCtr=0; m_IntCtr < m_ArraySize; m_IntCtr++)
 {     
  if (1 == MsgSent[m_IntCtr].FreeCell)
  {
   m_Current = m_IntCtr;
	 //TRACE ("Get_Free returns %d.\n", m_Current);
	 //printf("Get_Free returns %d.\n", m_Current);
	 m_CellCntr++; // counter of used cells.
   return m_Current;
  }
 } 
 // TRACE("Get_Free returns 0, because no free cells.\n"); 
 //printf ("Get_Free returns 0, because no free cells.\n"); 
 m_Current = 0;		 
 return 0; // in case, there are no any free cells...
}

void  DynBuff::PutMsgToStore(char * InMsg, int MsgSize)
{
  //***********************************************************************
	// function saves a message to a next free cell.
	//***********************************************************************
  int i;
  // printf ("PutMsgToStore called...\n");
  i = Get_Free();
  MsgSent[i].FreeCell =  0; // set to "reserved"...
  //********overflow warning****************************************
	if (MsgSize > 500)
		TRACE ("ERROR: DynBuffer overflow!!, > %d", MsgSize);
  //****************************************************************
  memcpy((void *)(MsgSent[i].Msg), (const void*)InMsg, MsgSize);
  MsgSent[i].MsgLen = MsgSize;
  MsgSent[i].MsgCntr = (unsigned int)InMsg[3]; // calculate from Msg[]
  MsgSent[i].MobId = (unsigned int)InMsg[4]; // Get MOB identity
  MsgSent[i].MsgNumber = (unsigned char)InMsg[5]; // Get Message number (200 or some..)
  MsgSent[i].ReSendCntr = 0;  
  SetGlobalFlag(1);
	//TRACE ("DynBuff::PutMsgToStore: MsgSize = %d, MsgNumber=%d\n", MsgSize, MsgSent[i].MsgNumber);	
}

int DynBuff::HandleMsgCtr(int Nbr)
{
	//***********************************************************************
	// function checking how many times current message was re-sended to 
	// PCC/SCR and if this amount is more than m_ReSendNum (i.e. - 5), returns 
	// FALSE and erase the current cell. In other case its return TRUE.
	//************************************************************************

	MsgSent[Nbr].ReSendCntr++; 
	//printf ("::HandleMsgCtr - MsgSent[%d].ReSendCntr = %d\n", Nbr, MsgSent[Nbr].ReSendCntr);
	if (m_ReSendNum <= MsgSent[Nbr].ReSendCntr)
		{
		 ResetCell(Nbr);		 
		 return FALSE;
		}	
	return TRUE;
}

int DynBuff::GetMsgFromStore(char * Msg, int Nbr)
{
 memcpy((void *)(Msg), (const void*)MsgSent[Nbr].Msg, MsgSent[Nbr].MsgLen);
 return MsgSent[Nbr].MsgLen;
} 

int DynBuff::GetGlobalFlag()
{
  return m_GlobFlag;
} 

int DynBuff::Get_MsgSize(int Nbr) 
{
 return MsgSent[Nbr].MsgLen;  
}

int DynBuff::Get_MobId(int Nbr) 
{
 return MsgSent[Nbr].MobId;  
}

int DynBuff::Get_MsgNbr(int Nbr) 
{
 return MsgSent[Nbr].MsgNumber; 
}

int DynBuff::EraseMsgFromStore (char * InMsg)
{
 int t_MobId;
 int t_CNT;
 
 t_MobId = InMsg[4]; // Get MOB identity
 t_CNT = InMsg[3]; // Get msg counter value
 
 for (m_IntCtr=0; m_IntCtr < m_ArraySize; m_IntCtr++)
 {    
	if (0 == MsgSent[m_IntCtr].FreeCell) 
	{
   // printf ("Compare with: MobId=%d, CNT=%d\n", MsgSent[m_IntCtr].MobId, MsgSent[m_IntCtr].MsgCntr);
	 TRACE  ("Compare with: MobId=%d, CNT=%d\n", MsgSent[m_IntCtr].MobId, MsgSent[m_IntCtr].MsgCntr);
	 if ((MsgSent[m_IntCtr].MobId == t_MobId) &&  (MsgSent[m_IntCtr].MsgCntr == t_CNT) )
	 {
		 ResetCell(m_IntCtr);
		 // here we probably must set another global flag, for sending something to COSMOS...
		 return TRUE;
	 }
	}
 }
 return FALSE; // no such messages...
}
 
void DynBuff::SetGlobalFlag(int Value)
{
  if (1 == Value)
  {
    m_GlobFlag = 1; // there is something to send
  }
  else
  {
   m_GlobFlag = 0; // nothing to send at all.
  }
}

int DynBuff::Get_CellCtr(void) 
{
 return m_ArraySize;
}

int DynBuff::GetCellBusy(int Nbr)
{
  if (0 == MsgSent[Nbr].FreeCell)
    return TRUE;
  else
   return FALSE;
}
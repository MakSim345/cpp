#include <iostream>
// #include "stdafx.h"

#include "gen.h"
#include "RingBuffer.h"
#include "trace.h"

#define YS_TEST_234089342
#ifdef YS_TEST_234089342

// extern Trace trc;

/********************************************************************

  Declaration: Function prints dump of message store
  Call: PrintDump()
  Input: nothing
  Returns: nothing
  08.05.2008 Initial coding YS.

*********************************************************************/
void DynBuff::PrintDump ()
{
   TRACE("\n---------------------------------------------------------\n");
   TRACE("DynBuffer Dump: Head: " << m_Head << ", Tail: " << m_Tail << "\n");
   
   //MsgSent[m_Tail].MsgId = nMsgId;  
   //MsgSent[m_Tail].Param = nParam;
   //MsgSent[m_Tail].MsgCntr = 0;  
      
   for (int i=0; i<m_ArraySize; i++)
   {
    TRACE("MsgSent["<<i<<"].MsgId = " << MsgSent[i].MsgId << "\n");
   }
   TRACE("\n---------------------------------------------------------\n");
}

/********************************************************************

  Declaration: Constructor with one parameter - buffer size.
  Call: DynBuff()
  Input: nothing
  Returns: nothing
  08.05.2008 Initial coding YS.

*********************************************************************/
DynBuff::DynBuff(int buffer_size ):
  m_ArraySize(buffer_size),
  m_CellCntr(0),
  m_Tail(0),
  m_Head(0),
  m_MsgExistFlag(0),
  m_nOverflowFlag(0)
{
 //printf ("Constructor. buffer_size  = %d\n", buffer_size );
  MsgSent = new VCMsgSent[m_ArraySize];
  
  for (m_IntCtr=0; m_IntCtr < m_ArraySize; m_IntCtr++)
     ResetCell(m_IntCtr); 

}
     
/********************************************************************

  Declaration:  Default constructor. 
  Call: DynBuff()
  Input: nothing
  Returns: nothing
  08.05.2008 Initial coding YS.

*********************************************************************/
DynBuff::DynBuff():
  m_ArraySize(300),
  m_CellCntr(0),
  m_Tail(0),
  m_Head(0),
  m_MsgExistFlag(0),
  m_nOverflowFlag(0)
{
 
 MsgSent = new VCMsgSent[m_ArraySize];
 
 for (m_IntCtr=0; m_IntCtr < m_ArraySize; m_IntCtr++)
     ResetCell(m_IntCtr);  
}

/********************************************************************

  Declaration:  Default destructor. 
  Call: ~DynBuff()
  Input: nothing
  Returns: nothing
  08.05.2008 Initial coding YS.

*********************************************************************/

DynBuff::~DynBuff()
{
 return;
}

/********************************************************************

  Declaration: Function resets the given cell.
  Call: ResetCell()
  Input: cell number, int.
  Returns: none
  08.05.2008 Initial coding YS

*********************************************************************/
void DynBuff::ResetCell(int nNbr)
{
  MsgSent[nNbr].FreeCell      =  1;
  MsgSent[nNbr].MsgId         = -1;  
  MsgSent[nNbr].Param         = -1;
  MsgSent[nNbr].MsgCntr       = -1;
  MsgSent[nNbr].ReSendCntr    = -1;

  decCellCtr();
}

/********************************************************************

  Declaration: Function decrement the cell counter and set MsgExistFlag
               to zero if no cells are in use.
  Call: decCellCtr()
  Input: none
  Returns: none
  15.05.2008 Initial coding YS

*********************************************************************/
void DynBuff::decCellCtr(void)
{
  // Check if there any cell are in use. 
  // If not - reset global flag: nothing to send anymore.
  m_CellCntr--;

  if (m_CellCntr < 0)
      m_CellCntr=0;
      
// t.itrace("DynBuff::decCellCtr m_CellCntr %d.  Time: %d\n", m_CellCntr, Get1msTimeMS());     
      
  if (0 == m_CellCntr)
  {
     setMsgExistFlag(0);
     //t.itrace("DynBuff::decCellCtr setMsgExistFlag(0).  Time: %d\n", Get1msTimeMS()); 
  }
}

/********************************************************************

  Declaration: Function increment the cell counter and set MsgExistFlag.
  Call: incCellCtr()
  Input: none
  Returns: none
  15.05.2008 Initial coding YS

*********************************************************************/
void DynBuff::incCellCtr(void)
{
  
  if (m_nOverflowFlag)
  {
    m_nOverflowFlag = 0;
    return; // do not increment cells in case of overflow.
  }
    
  m_CellCntr++;
  
  if (m_CellCntr < 0)
      m_CellCntr=0;
      
  if (m_CellCntr)
     setMsgExistFlag(1);
}

/********************************************************************

  Declaration: Function returns number of cells in use.
  Call: getCellCtr()
  Input: none
  Returns: int
  15.05.2008 Initial coding YS

*********************************************************************/
int DynBuff::getCellCtr(void)
{
  return m_CellCntr;  
}

/********************************************************************

  Declaration: Function returns m_Head value.
  Call: getHead()
  Input: nothing
  Returns: int
  15.05.2008 Initial coding YS

*********************************************************************/
int DynBuff::getHead()
{ 
  return m_Head; 
}

/********************************************************************

  Declaration: Function returns m_Tail value.
  Call: getTail()
  Input: nothing
  Returns: int
  15.05.2008 Initial coding YS

*********************************************************************/
int DynBuff::getTail()
{ 
  return m_Tail; 
}

/********************************************************************

  Declaration: Function saves a message to a next free cell.
  Call: putMsgToStore()
  Input: nothing
  Returns: nothing
  08.05.2008 Initial coding

*********************************************************************/
void  DynBuff::putMsgToStore(int nMsgId, int nParam)
{  
  int i = 0;   
 /*
 if ( m_CellCntr >= m_ArraySize )
    return -1;
 */   
 
 // t.itrace("DynBuffer: put message %d to cell(tail) %d\n", nMsgId, m_Tail);
  
  //********overflow warning****************************************
  if (MsgSent[m_Tail].FreeCell == 0)
  {
      m_nOverflowFlag = 1;
      TRACE ("ERROR: DynBuffer overflow in cell " << m_Tail << " !!\n");
  }
  //****************************************************************

  MsgSent[m_Tail].FreeCell =  0; // set to "reserved"...
  
  MsgSent[m_Tail].MsgId = nMsgId;  
  MsgSent[m_Tail].Param = nParam;
  MsgSent[m_Tail].MsgCntr = 0;  
  
  m_Tail++;
  
  // PrintDump();
  
  if ( m_Tail >= m_ArraySize )
  {     
    m_Tail = 0;      
  }
  
  incCellCtr();
}

/********************************************************************

  Declaration: Function reads the cell with given number and returns
               the value. Reserved for future use.
  Call: readMsgFromStore(int)
  Input: int
  Returns: int
  08.05.2008 Initial coding

*********************************************************************/
int DynBuff::readMsgFromStore(int nNbr)
{
 
 int nRetVal = 0;
 
 nRetVal = MsgSent[nNbr].Param;    
    
 return nRetVal;
}
/********************************************************************

  Declaration: Function 
  Call: getMsgFromStore()
  Input: nothing
  Returns: nothing
  08.05.2008 Initial coding

*********************************************************************/
int DynBuff::getMsgFromStore(int *nRetParam, int *nRetMsgId)
{ 
 int nRetVal = 0;
 
  //PrintDump();
 
 if ( !m_CellCntr )
   return -1;
  
  *nRetParam = MsgSent[m_Head].Param;
  *nRetMsgId = MsgSent[m_Head].MsgId;
  
  // t.itrace("DynBuffer: get message %d from cell %d.  Time: %d\n", *nRetMsgId, m_Head, Get1msTimeMS()); 
  
  ResetCell(m_Head);
  
  m_Head++;
  if ( m_Head >= m_ArraySize )
    m_Head = 0;
        
 return nRetVal;
} 

/********************************************************************

  Declaration: Check if message buffer is empty.
  Call: incCellCtr()
  Input: none
  Returns: if any message exist in buffer - returns 0, else 1.
  15.05.2008 Initial coding YS

*********************************************************************/
int DynBuff::isEmpty()
{
  return !m_MsgExistFlag;
} 

/********************************************************************

  Declaration: Get the message size from the cell.
  Call: getMsgSize(int)
  Input: int - cell number.
  Returns: function returns 1 all the time. Reserved for future use.
  15.05.2008 Initial coding YS

*********************************************************************/
int DynBuff::getMsgSize(int Nbr) 
{
 return 1;  
}

/********************************************************************

  Declaration: Get the message ID from the cell.
  Call: getMsgId(int)
  Input: int - cell number.
  Returns: integer - message ID.
  15.05.2008 Initial coding YS

*********************************************************************/
int DynBuff::getMsgId(int Nbr) 
{
 return MsgSent[Nbr].MsgId; 
}

/********************************************************************

  Declaration: Set private member m_MsgExistFlag to given value.
  Call: setMsgExistFlag()
  Input: int
  Returns: none
  08.05.2008 Initial coding YS

*********************************************************************/ 
void DynBuff::setMsgExistFlag(int Value)
{
  if (1 == Value)
  {
    m_MsgExistFlag = 1; // there is something to send
  }
  else
  {
   m_MsgExistFlag = 0; // nothing to send at all.
  }
}

/********************************************************************

  Declaration: Get the m_ArraySize, number of all cells in buffer.
  Call: getAllCellCtr(int)
  Input: none
  Returns: int
  15.05.2008 Initial coding YS

*********************************************************************/
int DynBuff::getAllCellCtr(void) 
{
 return m_ArraySize;
}

/********************************************************************

  Declaration: Check if given cell is busy. Reserved for future use.
  Call: getCellBusy(int)
  Input: int.
  Returns: 1 if cell is free, else 0.
  15.05.2008 Initial coding YS

*********************************************************************/
int DynBuff::getCellBusy(int Nbr)
{
  if (0 == MsgSent[Nbr].FreeCell)
    return 1;
  else
   return 0;
}

// End of class implementation.


#endif//  YS_TEST_234089342

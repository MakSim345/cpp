#include "gen.h" 
#include "crc_calc.h"

extern long g_lTimeTick;

/*-----------------------------------------------------------------------  
  Call: ret=CalcCS(transmit,string,nbrofchars,recvCS)
  Input: int               transmit (1 = transmit, 0=receive)
         unsigned char * string     target string
         int nbrofchars    how many chars are there to be calculated
         unsigned char recvCS       received CS (if transmit = 0)
  Returns: unsigned char ret (if transmit=1 -> CS,  if transmit=0 -> 0 (error)
                     or 1 (CS OK)
  Original Coding: 

  -----------------------------------------------------------------------
*/

unsigned char CalcCS(int transmit, unsigned char * string, int nbrofchars, unsigned char recvCS)
{
  int i;
  unsigned char CRC=0;

  //  calculate CS
  for (i=0; i < nbrofchars; i++)
    {
     CRC = CRC ^ string[i];
    }

  if (transmit)
     return(CRC);
  else
   {
    if (CRC == recvCS)
       return(1);
    else
     {    
#if defined DEBUG
      int j;
      printf("CRC Error: %x %x *",CRC,recvCS);
      for (j=0; j<nbrofchars; j++)
         printf("/%d",string[j]);
#endif
      return(0);
     }
   }    
}



/*
Calculates a CRC value to be used by CRC calculation functions.
*/
unsigned long CRC32Value(int i)
{
  int j;
  unsigned long ulCRC;

  ulCRC = i;
  for(j=8;j>0;j--)
  {
    if(ulCRC & 1)
      ulCRC = (ulCRC>>1)^CRC32_POLYNOMIAL;
    else
      ulCRC>>=1;
  }

  return ulCRC;
}

/*
Calculates the CRC-32 of a block of data all at once
ulCount: Number of bytes in the data block
ucBuffer: Data block
*/
unsigned long CalculateBlockCRC32(unsigned long ulCount, unsigned char* ucBuffer)
{
    unsigned long ulTemp1;
    unsigned long ulTemp2;
    unsigned long ulCRC = 0;

    while( ulCount-- != 0 )
    {
        ulTemp1 = ( ulCRC>>8 ) & 0x00FFFFFFL;
        ulTemp2 = CRC32Value( ((int)ulCRC ^ *ucBuffer++) & 0xFF );
        ulCRC = ulTemp1 ^ ulTemp2;
    }

    return ulCRC;
}

//*********************************************************************

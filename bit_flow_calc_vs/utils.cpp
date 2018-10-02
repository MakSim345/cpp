#include "gen.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "utils.h"

#define TEST12341412343

#ifdef TEST12341412343
CRC_Struct CRC_Calculation (unsigned char * str, int NumbOfChars)
{
 CRC_Struct CRC_Struct;
 unsigned char CRC;
 int i;

for (i=0; i<NumbOfChars; i++)
{
  CRC = (CRC + (unsigned char)str[i]) % 0xFFFF;
  // TRACE  ("str[%d]=%d CRC = %d / ", i ,(unsigned char) str[i], CRC);
}
//TRACE  ("CRC = %d 0x%X\n", CRC, CRC);
//TRACE  ("CRC>>8 = %d 0x%X\n", (CRC>>8), (CRC>>8));
//TRACE  ("CRC & 255 = %d 0x%X\n", (CRC & 255), (CRC & 255));
 CRC_Struct.CRC[0]=(CRC >> 8);
 CRC_Struct.CRC[1]=(CRC & 255);
return CRC_Struct;
}
#endif

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
unsigned long CalculateBlockCRC32(
                                  unsigned long ulCount,
                                  unsigned char* ucBuffer)
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
void AddShortTimeStamp(int *pos,char * msg)

//      Concanates timestamp for IPA TOS, in format:
//      HHMMSS
{
    char datetime[6];
    time_t seconds;

    // gettime(&t);
    seconds = time (NULL);
    // sprintf(datetime, "%02d%02d%02d",  t.ti_hour, t.ti_min, t.ti_sec);

   for (int i=0; i<6; i++)
     {
     *msg=datetime[i];
     msg++;
     }
   *pos=*pos+6;
}
/********************************************************************

  Savcor One Oy
  Declaration:  Adds a string to the string
  Call: AddStringPan()
  Input:
  Returns:

*********************************************************************/

void AddStringPan(char * destStr, char * strToAdd,int len)

//    Concanates string to msg string. Adds also spaces if needed.
{
    int cntr = 0;

   if (strlen(strToAdd) > (unsigned)len)
     {
     strToAdd[len] = 0; // cut the string if too long
     }

   for (cntr=0;cntr<len;cntr++) // replace underlines with blanks
      {
      if (strToAdd[cntr] == '_')
         {
         strToAdd[cntr] = ' ';
         }
      }

    cntr = len - strlen(strToAdd);
    strcat(destStr,strToAdd);
    for (;cntr > 0;cntr--)
    {
        strcat(destStr," "); // add enough spaces
    }
}

//*********************************************************************
void AddTimeStamp(int *pos,char * msg)

//      Concanates timestamp for SPARCS Movement msg.Timestamp format:
//      YYYYMMDDHHmmSS
{
    char datetime[14];
    //struct time t;
    //struct date d;

    //getdate(&d);
    //gettime(&t);
    // sprintf(datetime,"%d%02d%02d%02d%02d%02d", d.da_year,d.da_mon,d.da_day, t.ti_hour,t.ti_min,t.ti_sec);

   for (int i=0; i<14; i++)
     {
     *msg=datetime[i];
     msg++;
     }
   *pos=*pos+14;
}

#include <stdio.h>
#include <string.h>
#include "gen.h"
#include "time.h"
#include "dos.h"
#include <sys/stat.h>
#include <stdlib.h>
#include "utils.h"

/*-----------------------------------------------------------------------

Returns Time/Date String

  -----------------------------------------------------------------------*/
std::string PrintTime(void)
{
    //char ReturnTime[100];
    //struct date d;
    //struct time t;

    //getdate(&d);
    //gettime(&t);

    /*
    sprintf(ReturnTime,"%02d/%02d/%02d %02d:%02d:%02d",
           d.da_day,d.da_mon,d.da_year,
           t.ti_hour,t.ti_min,t.ti_sec);  // timestamp
    */

    // return ReturnTime;

    std::string ReturnTime;
    std::time_t t = std::time(NULL);
    std::tm tm_info = *std::localtime(&t);
    // std::cout.imbue(std::locale("ru_RU.utf8"));
    put_time(&tm_info, "%c %Z");    
    //cout << "PrintTime: " << t << "\n";
    //cout << "PrintTime: " << asctime(&tm_info) << "\n";

    // return ReturnTime;
    return asctime(&tm_info);
}


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

/*
int rand()
{
  // from K&R - produces a random number between 0 and 32767.
 int rand_seed = RND_MAX;

    rand_seed = rand_seed * 1103515245 +12345;
    return (unsigned int)(rand_seed / 65536) % 32768;
}
*/
int RND_Array()
{

#define RND_VAL  7
    int i,t,x,y;
    int a[RND_VAL]= {0, 0, 0, 0, 0, 0, 0};
    int random;
    int flag=0;
    /* fill array */
    // srand (time (NULL));

    for (i=0; i < RND_VAL; i++)
    {
        while(!flag)
        {
            random = 1 + (rand() % 39);
            //printf (": %d", random);
            if ((random > 0) && (random <= 39))
            {
                flag= 1;
                for (x=0; x < RND_VAL; x++)
                {
                    if (random == a[x])
                    {
                        flag= 0;
                        // printf ("%d is already in the array\n", random);
                        //printf ("-x ");
                    }
                }
            }
        }
        a[i]= random;
        flag = 0;
        srand (time (NULL));
        // printf("a[%d] = %d\n",i, a[i]);
   }

    /* bubble sort of an array */
    for (x=0; x < RND_VAL-1; x++)
        for (y=0; y < RND_VAL-x-1; y++)
            if (a[y] > a[y+1])
            {
                t=a[y];
                a[y]=a[y+1];
                a[y+1]=t;
            }

    /* print sorted array */
    //printf("\n--------------------\n");
    for (i=0; i < RND_VAL; i++)
    {
        // printf("a[%d] = %d\n",i, a[i]);
        if (a[i] < 10)
            printf("0%d ", a[i]);
        else
            printf("%d ", a[i]);
        // a[i] = 0;
    }

    printf("\n");
    return 0;
}



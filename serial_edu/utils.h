#ifndef UTILS_H
#define UTILS_H
/*********************************************************************

  utils.h  
  01.10.2004 Initial coding YS
  Consists CRC routins definitions.
**********************************************************************/

#define CRC32_POLYNOMIAL 0xEDB88320L
typedef struct
{
 int CRC[2];
}
CRC_Struct;

struct date
{
    int da_year;   
    char da_day;   
    char da_mon;   
};

unsigned long CalculateBlockCRC32(unsigned long, unsigned char*);

unsigned char CalcCS(int, unsigned char * , int, unsigned char);

CRC_Struct CRC_Calculation (unsigned char * str, int NumbOfChars);

void AddTimeStamp(int *pos,char * msg);
void AddStringPan(char * destStr, char * strToAdd,int len);
void AddShortTimeStamp(int *pos,char * msg);

#endif

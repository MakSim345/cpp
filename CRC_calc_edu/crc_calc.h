#ifndef CRC_CALC_H
#define CRC_CALC_H        
/*********************************************************************
  Consists CRC routins definitions.
**********************************************************************/
        
#define CRC32_POLYNOMIAL 0xEDB88320L

unsigned long CalculateBlockCRC32(unsigned long, unsigned char*);
unsigned char CalcCS(int, unsigned char * , int, unsigned char);
unsigned long CRC32Value(int i);

// CRC_Struct CRC_Calculation (unsigned char * str, int NumbOfChars);

#endif

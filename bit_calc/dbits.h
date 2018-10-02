#ifndef DBITS_H
#define DBITS_H        
/*********************************************************************

  dbits.h            
  01.10.2004 Initial coding YS          

**********************************************************************/        
        
void dispBits(unsigned Val, int nPrintRes);
void dispBitsToFile(unsigned Val, const char *FileNameF);
const char* byte_to_binary(int x);
        
#endif        

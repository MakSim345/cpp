#ifndef DBITS_H
#define DBITS_H        
/*********************************************************************

  dbits.h            
  01.10.2004 Initial coding YS          

**********************************************************************/        
#include "gen.h"

void dispBits(unsigned Val, int nPrintRes);
void dispBitsToFile(unsigned Val, const char *FileNameF);
void BitCalculation(unsigned Val, int nPrintRes, double* ArrONE, double* ArrZERO);
arrZero bitCalc(unsigned Val, int nPrintRes);
#endif

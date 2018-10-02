#include <stdio.h>

#include "binary.h"

void dispBits(unsigned Val, int nPrintRes)
{
    unsigned   c;
    unsigned   dispMask=1<<15;
    int        nBin;
 
    if (nPrintRes)
    {
        printf ("Val = %d\n", Val);
    }
 
    for (c = 1; c<=16; c++)
    {
        nBin = Val & dispMask ? 1 : 0 ;
    	if (nPrintRes)
        {
	       printf ("%d", nBin);
        }
	
        Val<<=1;
    	
        if ((c%8 == 0) && nPrintRes)
        {
	       printf (" ");       
        }
    }

    if (nPrintRes)
    {
        printf ("\n");
    }
}
#include <stdio.h>
#include <string.h>
#include "gen.h"
#include "dbits.h"


void dispBits(unsigned Val, int nPrintRes)
{
    unsigned BIT = 7;
    // unsigned BIT = 15;
    // unsigned   BIT = 30;
    unsigned   c;
    unsigned   dispMask=1<<BIT;
    int        nBin;

    //if (nPrintRes)
    //    printf ("Val = %d(0x%X)\n", Val, Val);

    for (c = 1; c<=BIT+1; c++)
    {
        nBin = Val & dispMask ? 1 : 0 ;

        if (nPrintRes)
            printf ("%d", nBin);

        Val<<=1;

        if ((c%8 == 0) && nPrintRes)
            printf (" ");
    }

    //if (nPrintRes)
    //    printf ("\n");
}

void dispBitsToFile(unsigned Val, const char* FileNameF)
{
 unsigned BIT = 7;
 //unsigned BIT = 15;
 //unsigned   BIT = 30;
 unsigned   c;
 unsigned   dispMask=1<<BIT;
 int        nBin;
 int nPrintRes = 1;
 FILE *fi = NULL;

if ( (fi = fopen(FileNameF, "a+") ) != NULL)
{

 if (nPrintRes)
    fprintf (fi, "Val = %d(0x%X)\n", Val, Val);

 for (c = 1; c<=BIT+1; c++)
 {
     nBin = Val & dispMask ? 1 : 0 ;
     if (nPrintRes)
       fprintf (fi, "%d", nBin);
     Val<<=1;
     if ((c%8 == 0) && nPrintRes)
         fprintf (fi, " ");
 }
 if (nPrintRes)
   fprintf (fi, "\n");
 fclose (fi);
 } // if fopen
}

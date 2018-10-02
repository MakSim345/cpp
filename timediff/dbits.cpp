#include "dbits.h"

arrZero bitCalc(unsigned Val, int nPrintRes)
{
    arrZero _zero;
    unsigned BIT = 7;
    //unsigned BIT = 15;
    //unsigned   BIT = 30;
    unsigned   c;
    unsigned   dispMask=1<<BIT;
    int        nBin;
 
    for (c = 1; c<=BIT+1; c++)
    {
        nBin = Val & dispMask ? 1 : 0 ;
        if (1==nBin)
        {
            _zero.one = _zero.one +1;
            //printf ("ONE = %.0f\n", *ArrONE);
        }
        else if (0==nBin)
        {
            _zero.zero = _zero.zero + 1;
            //printf ("ZERO = %.0f\n", *ArrZERO);
        }                       
      
        if (nPrintRes)
            printf ("%d", nBin);
     
        Val<<=1;
         
        if ((c%8 == 0) && nPrintRes)
            printf (" ");       
    }
 
    if (nPrintRes)
        printf (" ");

    return _zero;
}

void BitCalculation(unsigned Val, int nPrintRes, double* ArrONE, double* ArrZERO)
{
    unsigned BIT = 7;
    //unsigned BIT = 15;
    //unsigned   BIT = 30;
    unsigned   c;
    unsigned   dispMask=1<<BIT;
    int        nBin;
 
    /*if (nPrintRes)
    {
        printf ("0x%X ", Val);
    //printf ("%c", Val);
    }*/
     
    for (c = 1; c<=BIT+1; c++)
    {
        nBin = Val & dispMask ? 1 : 0 ;
        if (1==nBin)
        {
            *ArrONE = *ArrONE +1;
            //printf ("ONE = %.0f\n", *ArrONE);
        }
        else if (0==nBin)
        {
            *ArrZERO = *ArrZERO + 1;
            //printf ("ZERO = %.0f\n", *ArrZERO);
        }
        if (nPrintRes)
        {
            printf ("%d", nBin);
        }     
        Val<<=1;
         
        //if ((c%8 == 0) && nPrintRes)
        //    printf (" ");       
    }
 
    if (nPrintRes)
        printf (" ");
}
        


void dispBits(unsigned Val, int nPrintRes)
{
 unsigned BIT = 7;
 //unsigned BIT = 15;
 //unsigned   BIT = 30;
 unsigned   c;
 unsigned   dispMask=1<<BIT;
 int        nBin;
 
 if (nPrintRes)
    printf ("Val = %d(0x%X)\n", Val, Val);
 
 for (c = 1; c<=BIT+1; c++)
 {
     nBin = Val & dispMask ? 1 : 0 ;
     if (nPrintRes)
       printf ("%d", nBin);
     Val<<=1;
     if ((c%8 == 0) && nPrintRes)
         printf (" ");       
 }
 if (nPrintRes)
   printf ("\n");
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

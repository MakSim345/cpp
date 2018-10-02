#include <stdio.h>
#include <string.h>
#include "gen.h"
#include "dos.h"
#include <stdlib.h>
#include "utils.h"
#include "dbits.h"
#include "cube_calc.h"
#include "filter_calc.h"

/*
 *Usage:
    biton(myvar,3);
    bitoff(myvar,5);
    invertbit(myvar,1);
    if (testbit(myvar,6)) myvar=0;
 * */


void showDouble();
void showInt(int nVal = 0);
    
struct segments
{
    int age;
    int height;
    int weight;

    // int myints[7] = {32, 71, 12, 45, 26, 80, 53, 33};
};


int main( int argc, char *argv[] )
{

    long LastTimeIn=0;    
    long LastTimeInMS = 0;    
    int RValue = false;
    int Counter=0;  
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;

    printf ("main - start\n");
    // CTimer *_time = new CTimer ();
    
#ifdef YS9039384
    char* FileNameF = "Result.log";
    FILE *fi = NULL;
#endif

    // Res = 549755813.0;
    int iRes = 255;
    int iSub = 10;
    // 
    // CubeCalc *cc = new CubeCalc();
    int array[20] ={0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0xFF, 0xFB};
    // #define SETBITMASK(x, y) (x |= (y))
    //
    
    
    CircularBuffer cb_Air;    
    CircularBuffer cb_O2;
    CircularBuffer cb_Meth;
    CircularBuffer cb_Nitro;

    ElemType elem = {0};
    int testBufferSize = 10;

 
    cbInit(&cb_Air, testBufferSize);
    cbInit(&cb_O2, testBufferSize);
    cbInit(&cb_Meth, testBufferSize);
    cbInit(&cb_Nitro,  testBufferSize);

    /* Remove and print all elements
    while (!cbIsEmpty(&cb_N2O)) 
    {
        cbRead(&cb_N2O, &elem);
        printf("cb_N2O - %d\n", elem.value);
    }

    */
    
//*************MAIN LOOP*****************//
cout << "Press Ctr-X to exit." << std::endl;
int val_for_speed = 0;
do 
  {
    //This is simple Windows way:
    Sleep(500);

    /* Fill buffer with test elements 3 times */
    elem.value = val_for_speed++;// produceRND();
    
    
    //elem.value = produceRND();
    // elem.value = produceRND();
    // elem.value = produceRND();
    
    printf("-----------Buffer O2:\n");
    cbWrite(&cb_O2, &elem);
    cbPrintMe(&cb_O2);
    
    printf("-----------Buffer Air:\n");
    cbWrite(&cb_Air, &elem);
    cbPrintMe(&cb_Air);    
    
    printf("-----------Buffer Meth:\n");
    cbWrite(&cb_Meth, &elem);
    cbPrintMe(&cb_Meth);

    printf("-----------Buffer Nitro:\n");
    cbWrite(&cb_Nitro, &elem);
    cbPrintMe(&cb_Nitro);

    printf("---------------------------\n");
    //int filter = cbDoFiltering(&cb_O2);
    //printf("Average filter O2 = %d\n", filter);

    //filter = cbDoFiltering(&cb_Air);
    //printf("Average filter Air = %d\n", filter);

    //filter = cbDoFiltering(&cb_N2O);
    //printf("Average filter N2O = %d\n", filter);
    
    // while (getchar() != '\n');

    // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {
        // RValue = true;
        NewChar=(unsigned char)_getch();
        if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
        {
            RValue = true; // END mark
        }     
        if (NewChar == 'd')  // pressed
        {
            if (1 == CaptureModeHex) 
                CaptureModeHex = 1;
            else
                CaptureModeHex = 0;
        }
    }


} while (!RValue);  
    printf("\nApp end.\n");
    return 0;
}

void showInt(int nVal)
{
    int iRes = 0;
    if (nVal > 0)
        iRes = nVal;

    // printf("\nBinary INT start to show:\n");
    printf ("Binary value of %d:\n ", iRes);
    dispBits((unsigned)iRes, 1);
    printf ("\n");
}

void showDouble()
{
    unsigned char buffer[9];
    int i=0;
    double dRes = 132316.5;
    printf("\nBinary DOUBLE start to show:\n");

    printf ("sizeof(Res) = %d\n", sizeof(dRes) );
    memcpy((void *)(buffer), (const void*)&dRes, sizeof(dRes));

    for (i=0; i<8; i++)
    {
        printf ("[%d] = 0x%X\n", i, buffer[i]);
        dispBitsToFile(buffer[i], "BinHex.log");
        dispBits(buffer[i], 1);
    }
    
    printf ("number %ld in Hex format:\n", dRes);
    for (i=0; i<8; i++)
    {
        printf ("0x%X ", buffer[i]);
        //dispBitsToFile(buffer[i], "BinHex.log");
        //dispBits(buffer[i], 1);
    }

    printf ("number %ld in binary format:\n", dRes);
    for (i=0; i<8; i++)
    {
        // printf ("0x%X ", buffer[i]);
        //dispBitsToFile(buffer[i], "BinHex.log");
        dispBits(buffer[i], 1);
    }
    // return 0;
}

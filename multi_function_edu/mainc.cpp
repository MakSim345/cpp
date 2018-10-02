#include <stdio.h>
#include <string.h>
#include "gen.h"
#include "dos.h"
#include <stdlib.h>
#include "utils.h"
#include "dbits.h"
#include "cube_calc.h"
#include "filter_calc.h"
#include <stdarg.h>

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

void TRACE_VAR(const char *msg, ...)
{
	int count = 3;
    va_list arg;
    char smsg[256];
	va_start(arg, msg);
	// vsprintf(smsg, msg, arg);
    for (int i = 0; i < count; ++i) 
    {
        vsprintf(smsg, msg, arg);
    }
    // 
	va_end(arg);
	strcat(smsg,"\r\n");
	// sock_fastwrite(srv, smsg, strlen(smsg));
    printf (smsg);
}

void TRACE_VAR_2 (const char *format, ...)
{
   va_list arg;
   int done;
   char msg[255];
   va_start (arg, format);
   // done = vfprintf (stdout, format, arg);
   sprintf(msg, format, arg);
   
   printf (msg);

   va_end (arg);
}


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
    
    /* Remove and print all elements
    while (!cbIsEmpty(&cb_N2O)) 
    {
        cbRead(&cb_N2O, &elem);
        printf("cb_N2O - %d\n", elem.value);
    }

    */

    TRACE_VAR_2("TEST\n");
    TRACE_VAR_2("TEST - %d %d %d", 1, 2, 3);

    return 0;
    
//*************MAIN LOOP*****************//
cout << "Press Ctr-X to exit." << std::endl;
int val_for_speed = 0;
do 
  {
    //This is simple Windows way:
    Sleep(100);

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

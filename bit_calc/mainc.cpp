#include <stdio.h>
#include <string.h>
#include "gen.h"
#include "dos.h"
#include <stdlib.h>
#include "utils.h"
#include "dbits.h"
#include "cube_calc.h"

// #define YS9039384

#ifndef _AVR035_H_
#define _AVR035_H_

// from AVR035: Efficient C Coding for AVR

#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))

#define SETBITMASK(x, y) (x |= (y))
#define CLEARBITMASK(x, y) (x &= (~y))
#define FLIPBITMASK(x, y) (x ^= (y))
#define CHECKBITMASK(x, y) (x & (y))

#endif 

// Bit operations for general:
#define invertbit(x, y) (x^=(1<<y))
#define biton(x,y) (x|=1<<y)
#define bitoff(x,y) (x&=~(1<<y))
#define testbit(x,y) (x&(1<<y))
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
#ifdef YS9039384
    char* FileNameF = "Result.log";
    FILE *fi = NULL;
#endif

    if (argc >= 2)
    {
       int _to_convert = atoi(argv[1]);
       printf ("0b%s\n", byte_to_binary(_to_convert) );
       return 1;
    }   

    // Res = 549755813.0;
    int iRes = 255;
    int iSub = 10;
/*
    showInt(iRes);
    showInt(iSub);

    invertbit(iRes, 7);
    showInt(iRes);
    showInt(iSub);
*/
    // 
    // CubeCalc *cc = new CubeCalc();
    int array[20] ={0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0xFF, 0xFB};
    // #define SETBITMASK(x, y) (x |= (y))
    //
    //
    unsigned int _test_res = 11;
    int test_bit_num = 2;
    // showInt(_test_res);
    // printf ("Check bit: _test_res=%d\n", _test_res );

    unsigned int _test_res2 = 0;
    // printf ("_test_res2 origin:\n");
    // showInt(_test_res2);
    // _test_res2 = _test_res2 | 0x08;
    // SETBIT(_test_res2, 3);
    // CLEARBIT(_test_res2, 0);
    //#define SETBIT(ADDRESS, BIT) (ADDRESS |= (1<<BIT))
    //#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))    
    
    // showInt(_test_res2);
    // printf ("Check bit: _test_res2=%d\n", _test_res2);
    unsigned int ADCSRA;
    ADCSRA = 13;
    unsigned int _bit_number_to_set = 5;

    printf ("Origin number:\n", ADCSRA);
    showInt(ADCSRA);
    
    ADCSRA |= 1<<_bit_number_to_set;
    printf ("set bit %d to 1:\n", _bit_number_to_set);
    showInt(ADCSRA);

    // printf ("CHECKBIT(%d, %d) = %d\n\n", _test_res, test_bit_num, CHECKBIT(_test_res, test_bit_num) );

    unsigned int SENSOR_VALID = 0;
    SENSOR_VALID = 1 << 5;
    printf ("SENSOR_VALID = 1 << 5: %d\n", SENSOR_VALID);
    showInt(SENSOR_VALID);

    unsigned int SHIFT = 14;
    unsigned int SENSOR_VALIDITY_UNKNOWN = 0; 
    SENSOR_VALIDITY_UNKNOWN = 1 << SHIFT;
    printf ("SENSOR_VALIDITY_UNKNOWN = 1 << %d: %d\n", SHIFT, SENSOR_VALIDITY_UNKNOWN);
    showInt(SENSOR_VALIDITY_UNKNOWN);
    // printf ("0b%s\n", byte_to_binary(SENSOR_VALIDITY_UNKNOWN));
    
    int raw = 512 + 16384;
    showInt(raw);
    if (raw & SENSOR_VALIDITY_UNKNOWN)
        printf ("TRUE: SENSOR_VALIDITY_UNKNOWN and raw have same bit 512\n");
    else
        printf ("FALSE: SENSOR_VALIDITY_UNKNOWN and raw do not have same bit 512\n");

    return 1;


    int array_a[2] = {0xFC, 0x3};
    printf("Test: %d and %d will be shifted to << 4 \n", array_a[0], array_a[1]);
    showInt(array_a[0]);
    showInt(array_a[1]);
    // SETBITMASK(array_a[0], array_a[1]);
    int _res = (array_a[0] << 4) | array_a[1] ;
    showInt(array_a[0] << 4);
    //showInt(array_a[1]);
    showInt(_res);

    unsigned int _test3 = 0x55;    
    showInt(_test3);  
    
    int pos = 7;
    int _my_res = ((_test3 & (1 << pos)) == (1 << pos));
    // printf ("Check bit: _my_res=%d\n", _my_res);

    int _to_show = 128;
    int orig = 2;
    int _sft = 1;
    
    printf("Test: %d will be shifted to <<1 \n", orig);
    showInt(orig);
    showInt(orig<<_sft);
   
    printf("Test: %d will be shifted to 1<<5. \n", _to_show);
    showInt(_to_show);
    
    _to_show |= 1<<5; 
    printf("After 1<<5: %d\n", _to_show);
    showInt(_to_show);
    
    bitoff(_to_show, 1);
    showInt(_to_show);
    
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

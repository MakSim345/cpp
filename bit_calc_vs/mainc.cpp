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

#define SETBITMASK(x,y) (x |= (y))
#define CLEARBITMASK(x,y) (x &= (~y))
#define FLIPBITMASK(x,y) (x ^= (y))
#define CHECKBITMASK(x,y) (x & (y))

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
void set_number_int(int);
void set_number_float(float _to_write);
int get_random_int(int _min, int _max);

void init_rnd()
{
    srand (time (0));
}

float get_random_float()
{
    float _ret_value = 0.0;
    int _tmp_random = get_random_int(0, 999);
    
    _ret_value = _tmp_random / 100.0;
    return _ret_value;
}

int get_random_int(int _min, int _max)
{
    int _ret_value = 0;
    _ret_value = rand() % _max + _min;
    return _ret_value;
}

int main( int argc, char *argv[] )
{
#ifdef YS9039384
    char* FileNameF = "Result.log";
    FILE *fi = NULL;
#endif
    init_rnd();
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
    int _to_show = 128;
    int orig = 0xF;
    int _sft = 1;
    printf("Test: %d\n", orig);
    printf("Test: 0x%X\n", orig);
    showInt(orig);
    // orig |= 1<<7; 
    biton(orig, 7);
    // orig<<_sft;
    printf("Test: %d\n", orig);
    printf("Test: 0x%X\n", orig);
    showInt(orig);

    showInt(orig<<_sft);

    showInt(_to_show);
    _to_show |= 1<<5; 
    
    showInt(_to_show);
    
    bitoff(_to_show, 1);
    showInt(_to_show);
    
    set_number_int(get_random_int(0, 99));
    float _fl_tmp = get_random_float();
    printf("_fl_tmp: %lf\n", _fl_tmp);
    set_number_float(_fl_tmp);

    printf("\nApp end.\n");
    return 0;
}


void set_number_int(int _to_write)
{
    int firdstDigit = (_to_write - _to_write % 10)/10;
    int secondDigit = _to_write % 10;
    
    printf("set_number_int: firdstDigit %d\n", firdstDigit);
    printf("set_number_int: secondDigit %d\n", secondDigit);
    // TODO: perform range check for _LED: from 1 to 3.
    // int leftLED = _LED*2 - 1;
    // int rightLED = _LED*2;
    
    //max7219_Write(leftLED, firdstDigit);
    //max7219_Write(rightLED, secondDigit);
}

void set_number_float(float _to_write)
{
    int _tmp = int(_to_write * 10);
    int firdstDigit = (_tmp - _tmp % 10)/10;
    int secondDigit = _tmp % 10;
    
    printf("set_number_float: firdstDigit %d\n", firdstDigit);
    printf("set_number_float: secondDigit %d\n", secondDigit);
    // TODO: perform range check for _LED: from 1 to 3.
    // int leftLED = _LED*2 - 1;
    // int rightLED = _LED*2;
    
    //max7219_Write(leftLED, firdstDigit);
    //max7219_Write(rightLED, secondDigit);
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

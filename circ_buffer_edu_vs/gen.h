#ifndef GEN_H
#define GEN_H        
/*********************************************************************

  gen.h  
  01.10.2004 Initial coding YS          

**********************************************************************/
#define TRACE printf

#define MIN(x,y)     (((x) < (y)) ? (x) : (y))
#define MAX(x,y)     (((x) > (y)) ? (x) : (y))    

#include <stdio.h>
#include <conio.h>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define WIN32_APP

#ifdef WIN32_APP
  #include <Windows.h>
#endif

using namespace std;

// from AVR035: Efficient C Coding for AVR

#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))

#define SETBITMASK(x, y) (x |= (y))
#define CLEARBITMASK(x, y) (x &= (~y))
#define FLIPBITMASK(x, y) (x ^= (y))
#define CHECKBITMASK(x, y) (x & (y))

// Bit operations for general:
#define invertbit(x, y) (x^=(1<<y))
#define biton(x,y) (x|=1<<y)
#define bitoff(x,y) (x&=~(1<<y))
#define testbit(x,y) (x&(1<<y))


#endif GEN_H

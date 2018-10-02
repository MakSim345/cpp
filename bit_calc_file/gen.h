#ifndef GEN_H
#define GEN_H		
/*********************************************************************

  gen.h  
  01.10.2004 Initial coding YS  		

**********************************************************************/
#include <stdio.h>
#include <conio.h>
#include "time.h"
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>


using namespace std;

#ifndef TRUE
#define TRUE -1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#define IPAPckPlc 0x0A41
#define IPAHrtBt  0x0A31
#define IPAAckwg  0x0E29
#define TRACE printf
	
#define IPA_TOS_VER "SAV001"
#define IPA_HBEAT 100
	
#define MIN(x,y)     (((x) < (y)) ? (x) : (y))
#define MAX(x,y)     (((x) > (y)) ? (x) : (y))	

#define WIN32_APP
#define RND_MAX 65536

#ifdef WIN32_APP
  #include <Windows.h>
#endif

struct arrZero
{
    int zero;
    int one;
};

#endif GEN_H

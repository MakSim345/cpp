#ifndef GEN_H
#define GEN_H        

#ifndef TRUE
    #define TRUE -1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#define mkdir(path) mkdir(path,0700)
 
#define MIN(x,y)     (((x) < (y)) ? (x) : (y))
#define MAX(x,y)     (((x) > (y)) ? (x) : (y))    

#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <math.h>
#include <numeric>
#include <Windows.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>

#define DEBUG

using namespace std;
    
#endif GEN_H

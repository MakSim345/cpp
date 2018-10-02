#ifndef _GEN_H_
#define _GEN_H_

// detectin memory leak in VS:
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//---------------------

#include <stdio.h>
#include <conio.h>
#include "time.h"
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <math.h>
#include <Windows.h>
#include <signal.h>
#include <iostream>

using namespace std;


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define TIME_TICK_INTERVAL 1000

// This didn't work:
// #define rdtsc __asm __emit 0fh __asm __emit 031h

#define WIN32_APP
#define RND_MAX 65536

#endif

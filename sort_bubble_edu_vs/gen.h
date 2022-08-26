#pragma once

//#define WIN32_APP

#ifdef WIN32_APP
    #include <Windows.h>
    #include <conio.h> // for kbhit()
    #define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#endif

#include "utils.h"
#include "time.h"

#include <ctime>

//#include <unistd.h>  /* for sleep() : in Linux gcc */
#include <stdio.h>   /* printf */
#include <string.h>  /* strcat */
// #include <stdlib.h>  /* strtol */

#include <cstdlib> 
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
#include <cstdio>
#include <atomic>
#include <mutex>
#include <thread>
#include <chrono>
#include <fstream>
#include <map>
// #include <math.h>


#define TIME_TICK_INTERVAL 1000
#define RND_MAX 65536

// This didn't work:
// #define rdtsc __asm __emit 0fh __asm __emit 031h

using namespace std;

#pragma once

#include <stdio.h>
#include "utils.h"
#include <conio.h>
#include "time.h"
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <math.h>
#include <thread> // since C++11
#include <chrono> // since C++11

// those 2 need for mutex:
#include <mutex> 
#include <condition_variable>


#define WIN32_APP
#ifdef WIN32_APP
  #include <Windows.h>
#endif

using namespace std;

#define TIME_TICK_INTERVAL 1000

// This didn't work:
// #define rdtsc __asm __emit 0fh __asm __emit 031h
#define RND_MAX 65536



#pragma once

#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <math.h>

// #define WIN32_APP
#ifdef WIN32_APP
    #include <conio.h>
    #include <Windows.h>
#endif

#include <ctime>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define TIME_TICK_INTERVAL 1000

#define RND_MAX 65536

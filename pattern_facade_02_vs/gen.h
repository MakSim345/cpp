#pragma once

#define TIME_TICK_INTERVAL 1000

#define WIN32_APP

#include <stdio.h>
#include <conio.h>
#include "time.h"
#include <Windows.h>
#include "stdlib.h"
#include <iostream>
#include <string>
#include "TCHAR.h"

#ifdef _WIN32
    #include <windows.h>
#elif defined __linux__
    #include <unistd.h>
#endif

using namespace std;

void mySleep(unsigned int millisecs)
{
#ifdef _WIN32
    Sleep(millisecs);
#elif defined __linux__
    usleep(1000 * millisecs);
#endif
}

/* Uncomment below line to enable debug logs */
/* #define DEBUG */



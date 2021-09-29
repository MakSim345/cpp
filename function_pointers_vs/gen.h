#pragma once

#define TIME_TICK_INTERVAL 1000
#define WIN32_APP
#define RND_MAX 65536

#ifdef WIN32_APP
    #include <Windows.h>
#endif

#include "TCHAR.h"
#include "stdlib.h"
#include "time.h"
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/timeb.h>
#include <vector>

using namespace std;


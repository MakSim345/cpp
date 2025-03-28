#pragma once

#define TIME_TICK_INTERVAL 1000

#define RND_MAX 65536

// Include the appropriate header for each platform
// #define WIN32_APP
// #ifdef WIN32_APP
#ifdef _WIN32
    #include <Windows.h>
    #include <conio.h> // for kbhit()
#else
    /* for sleep() : in Linux gcc */
    #include <unistd.h>
#endif

#include <stdio.h>   /* printf */
#include <string.h>  /* strcat */
// #include <stdlib.h>  /* strtol */
#include <algorithm> // For std::sort

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
#include <random>
#include <map>
#include <ctime>
#include <sys/timeb.h>
#include "time.h"

using namespace std;

#define LOG(x) std::cout << x << std::endl;


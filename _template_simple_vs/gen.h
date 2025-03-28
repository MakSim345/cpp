#pragma once

#define TIME_TICK_INTERVAL 1000
#define WIN32_APP
#define RND_MAX 65536

#ifdef WIN32_APP
    #include <Windows.h>
#endif

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
#include <cstdio>
#include <thread>
#include <chrono>
#include <random>
#include <map>

#include <stdio.h>
#include <string.h>
#include <sys/timeb.h>

using namespace std;

#define LOG(x) std::cout << x << std::endl;

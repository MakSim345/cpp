#pragma once

#define TIME_TICK_INTERVAL 1000
#define RND_MAX 65536

// #define WIN32_APP
#ifdef WIN32_APP
    #include <Windows.h>
    #include "TCHAR.h"
    #include <conio.h>
#endif


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
#include "stdlib.h"
#include "time.h"
#include <stdio.h>
#include <string>
#include <sys/timeb.h>

using namespace std;

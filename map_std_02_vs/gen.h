#pragma once

#define TIME_TICK_INTERVAL 1000
#define RND_MAX 65536

#define MAX_NUMBER_LIST 1000000
// #define MAX_NUMBER_LIST 1000

// #define WIN32_APP
#ifdef WIN32_APP
    #include <Windows.h>
    #include <conio.h> // for kbhit()
#endif

// #include <ctime>
// #include <cstdlib>
// #include <atomic>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
#include <cstdio>
#include <mutex>
#include <thread>
#include <chrono>
#include <fstream>
#include <map>

using namespace std;

#pragma once

#define TIME_TICK_INTERVAL 1000
// #define RND_MAX 65536
#define RND_MAX 36

// Include the appropriate header for each platform
// #define WIN32_APP
//#ifdef WIN32_APP
#ifdef _WIN32
    #include <Windows.h>
    #include <conio.h> // for kbhit()
#else
    #include <unistd.h>
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


using namespace std;


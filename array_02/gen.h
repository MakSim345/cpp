#pragma once

#define TIME_TICK_INTERVAL 1000
// #define RND_MAX 65536
#define RND_MAX 1000000


// #define WIN32_APP
#ifdef WIN32_APP
    #include <windows.h> // For Windows
    #include <conio.h> // for kbhit()
#else
    #include <unistd.h> // For Linux/WSL
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
#include <random>

using namespace std;

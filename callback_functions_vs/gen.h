#pragma once

#define TIME_TICK_INTERVAL 1000
#define RND_MAX 65536

// #define WIN32_APP
#ifdef WIN32_APP
    #include <Windows.h>
    #include <conio.h> // for kbhit()
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
#include <math.h>



using namespace std;


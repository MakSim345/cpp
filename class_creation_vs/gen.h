#pragma once

#define TIME_TICK_INTERVAL 1000
#define WIN32_APP
#define RND_MAX 65536

#define WIN32_APP

#ifdef WIN32_APP
    #include <Windows.h>
    #include <conio.h> // for kbhit()
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
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


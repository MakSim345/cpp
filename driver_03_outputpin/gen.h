#pragma once

// #define WIN32_APP
#ifdef WIN32_APP
  #include <Windows.h>
  #include <conio.h>
#endif

#include <cstdio>
#include <iostream>
#include <atomic>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <map>
#include <stdio.h>

#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>

// #include <math.h>
#include <thread> // since C++11
#include <chrono> // since C++11

// those 2 need for mutex:
#include <mutex>
#include <condition_variable>

#include <queue>

using namespace std;
using namespace std::chrono_literals; // for 2000ms literal
using String = std::string;

typedef enum
{
    HAL_OK = 0x00,
    HAL_ERROR = 0x01,
    HAL_BUSY = 0x02,
    HAL_TIMEOUT = 0x03
} HAL_StatusTypeDef;

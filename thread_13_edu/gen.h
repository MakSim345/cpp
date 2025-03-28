#pragma once

// #define WIN32_APP
#ifdef WIN32_APP
  #include <Windows.h>
  #include <conio.h>
#endif

#include <cstdio>
#include <iostream>
#include <atomic>
#include <cassert>
#include <mutex>

#include <ctime>
#include <chrono>

// #include <stdio.h>

// #include "time.h"
// #include <string.h>
// #include "stdlib.h"
// #include <vector>
// #include <sstream>
// #include <fstream>
// #include <math.h>

#include <unistd.h> // needed for getpid()

#include <map>
#include <thread> // since C++11
#include <chrono> // since C++11

// those 2 need for mutex:
#include <mutex> 
#include <condition_variable>

#include <queue> 

// using namespace std;
using namespace std::chrono_literals; // for 2000ms literal

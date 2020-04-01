#pragma once

#define TIME_TICK_INTERVAL 1000

//#define WIN32_APP

#ifdef WIN32_APP
  #include <Windows.h>
#endif

#define _USE_MATH_DEFINES
#include <cmath>
#include <stdio.h>
// #include <conio.h>
#include "time.h"
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <ctime>
#include <unistd.h>

// #include "phone_book.h"

using namespace std;

#ifndef _GEN_H_
#define _GEN_H_

#include <stdio.h>
#include <ctime>
#include "stdlib.h"
#include <sstream>
#include <fstream>
#include <math.h>
#include <numeric>
#include <iostream>     // std::cout
#include <algorithm>    // std::count
#include <vector>       // std::vector

// Include the appropriate header for each platform
// #define WIN32_APP
// #ifdef WIN32_APP
#ifdef _WIN32
    #include <Windows.h>
    #include <conio.h> // for kbhit()
#else
    /* for sleep() : in Linux gcc */
    #include <unistd.h>
#endif

using namespace std;

#define RND_MAX 65536

#include <string>
#include <map>

using std::map;
using std::string;

#endif

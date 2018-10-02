
#include <stdio.h>
#include "utils.h"
#include <conio.h>
#include "time.h"
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <math.h>
#include <Windows.h>


//#include <boost/ptr_container/ptr_list.hpp>
//#include <boost/scoped_ptr.hpp>
//#include <boost/shared_ptr.hpp>

#include <iostream>
#include <iterator>
#include <algorithm>


using namespace std;

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define TIME_TICK_INTERVAL 1000


// This didn't work:
// #define rdtsc __asm __emit 0fh __asm __emit 031h

#define WIN32_APP
#define RND_MAX 65536



#ifndef _GEN_H_
#define _GEN_H_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <sstream>
#include <time.h>
#include <memory>

// #define LINUX
#define WINDOWS

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif



#define MAIN_LINE 100

#endif

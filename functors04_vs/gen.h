#pragma once

#define TIME_TICK_INTERVAL 1000
#define WIN32_APP

#ifdef WIN32_APP
#include <Windows.h>
#endif

#define RND_MAX 65536

#include "stdlib.h"
#include "time.h"
#include "utils.h"
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/timeb.h>
#include <vector>

using namespace std;


#ifndef _GEN_H_
#define _GEN_H_

#include <stdio.h>
#include <vector>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <memory>

// #define WIN32_APP
#ifdef WIN32_APP
    #include <conio.h> //for WIN32_APP
    #include <Windows.h>
#endif


using namespace std;

struct CityRecord
{
    std::string Name;
    uint64_t Population;
    double Latitude;
    double Longitude;
};

#endif

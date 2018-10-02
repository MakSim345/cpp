#ifndef _TEMPLATE_EDU_H_
#define _TEMPLATE_EDU_H_
//============================================================
//
//
//============================================================
//
// File:           templateEdu.h
//
//============================================================
// Description:
// Timer class
//============================================================
#include "stdlib.h"
#include <vector>

template <class T>
void printArray(T *my_array, const int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << my_array[i] << " ";
    }
    cout << "\n";
    return;
}

// template <class T> T& Max(T& a, T& b);
template <class T> 
T& Max(T& a, T& b) 
{
    if ( a >  b ) 
        return a; 
    else 
        return b;
}

#endif
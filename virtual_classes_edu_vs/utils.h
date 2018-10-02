#ifndef _UTILS_H_
#define _UTILS_H_		
#include "gen.h" 
#include "RandomNumbers.h"
		
int produceRND();
void printRandomNumbers();

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

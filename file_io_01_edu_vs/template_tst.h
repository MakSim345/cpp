#include "gen.h"


template <class My_Type>
My_Type maximum (My_Type value_1, My_Type value_2)
{
    My_Type max = value_1;
    if (value_2 > max)
        max = value_2;

    return max;
}

template <class superType>
superType Add( superType a, superType b) 
{ 
    return a + b;
}
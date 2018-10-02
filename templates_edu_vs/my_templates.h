#ifndef _MY_TEMPLATES_H_
#define _MY_TEMPLATES_H_
//============================================================
//
//
//============================================================
// Description:
//============================================================
#include "gen.h"

/*
void _usage()
{
    // Funct< int > cI(25);
    // Funct< double > cD(3.12);
    //cout << "cI " << cI.GetValue() << endl;
    //cout << "cD " << cD.GetValue() << endl;
    cout << "cI " << endl;
}
*/
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


template <class superType>
superType maximum (superType value_1, superType value_2)
{
    superType max = value_1;
    if (value_2 > max)
        max = value_2;

    return max;
}

template <class _anyType>
_anyType anyTypeAdd( _anyType a, _anyType b) 
{ 
    return a + b;
}

template <class superType>
superType fuct(superType value)
{
    return (value*value)-(2*value);
}

//*******************INT and Double example*************
template < class sTemplate >
class Funct
{
public:
    Funct(sTemplate value)
    {
        x=value;
    }
    sTemplate GetValue()
    {
        return (x*x)-(2*x);
    }
private:
    sTemplate x;
};

class CFucntInt
{
public:
    CFucntInt(int value)
    {
        x=value;
    }
    int GetValue()
    {
        return (x*x)-(2*x);
    }

private:
    int x;
};

class CFucntDouble
{
public:
    CFucntDouble(double value)
    {
        x=value;
    }
    double GetValue()
    {
        return (x*x)-(2*x);
    }

private:
    double x;
};

#endif

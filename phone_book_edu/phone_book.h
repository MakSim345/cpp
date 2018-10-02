#ifndef _PHONE_BOOK_H_
#define _PHONE_BOOK_H_
//============================================================
//
//
//============================================================
//
//
//============================================================
// Description:
//==========================================================
#include "gen.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Number
{
public:
    string name;
    string number;
    Number(const Number &v);
    Number();
    const Number &operator=(const Number &v)    
    {
        name = v.name;
        number = v.number;
        return v;
    }
};

#endif 

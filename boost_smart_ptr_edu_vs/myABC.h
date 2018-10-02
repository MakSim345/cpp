#ifndef _MY_ABC_CLASS_H_
#define _MY_ABC_CLASS_H_

//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

class myABC
{
public:    
    myABC(string arg) {_my_name = arg;}
    ~myABC() {std::cout << _my_name << " Destroyed!!!" << "\n";} 
    
    std::string _my_name;
    int i;
    float j;
};

#endif

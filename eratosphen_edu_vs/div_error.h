#ifndef _DIV_ERROR_H_
#define _DIV_ERROR_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include <stdio.h>
#include <iostream>

class DivideByZeroError
{
 public:
    DivideByZeroError();
    void printMesage() const;
 private:
    const char * message;
};
    
// float quotient(int num1, int num2);

#endif

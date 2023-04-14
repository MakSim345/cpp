//============================================================
//
// Description:
//============================================================

#include <stdio.h>
#include <iostream>

class DivideByZeroError
{
 public:
    DivideByZeroError();
    void printMesage() const;
 private:
    const char* messageP;
};
    
float quotient(int num1, int num2);


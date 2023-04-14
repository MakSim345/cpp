//============================================================
//
// Description:
//============================================================

#include <stdio.h>
#include <iostream>

class error_message
{
 public:
    error_message();
    void printMesage() const;
 private:
    const char * message;
};
    
float quotient(int num1, int num2);


#ifndef _ERROR_MESSAGE_H_
#define _ERROR_MESSAGE_H_

#include "gen.h"

class error_message
{
public:
    error_message();
    void printMessage() const;
private:
    const char* message;
};

float quotient(int num1, int num2);

#endif

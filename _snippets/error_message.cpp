//============================================================
//
//============================================================
//
// File:           error_message.cpp
//
//============================================================
// Description:
//============================================================
#include "error_message.h"

error_message::error_message() : 
    message("Attention - there is an error!\n")
{
 
}
void error_message::printMesage() const 
{
    printf ("%s", message);
}
    
float quotient(int num1, int num2)
{
 if (num2==0)
 {
      throw error_message ();
 }
 return (float) num1 / num2;
 
}

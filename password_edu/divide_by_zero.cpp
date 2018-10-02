//============================================================
//
// Description:
//============================================================
#include "divide_by_zero.h"

DivideByZeroError::DivideByZeroError() : 
    message("geLeHue Ha HoLb!\n")
{
 
}
void DivideByZeroError::printMesage() const 
{
    printf ("%s", message);
}
    
float quotient(int num1, int num2)
{
 if (num2==0)
 {
      throw DivideByZeroError ();
 }
 return (float) num1 / num2;
 
}

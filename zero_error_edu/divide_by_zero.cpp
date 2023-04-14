//============================================================
//
// Description:
//============================================================
#include "divide_by_zero.h"

DivideByZeroError::DivideByZeroError() : 
    messageP("ERROR (customer handler) - Divide to ZERO!\n")
{
 
}
void DivideByZeroError::printMesage() const 
{
    printf ("%s", messageP);
}


float quotient(int num1, int num2)
{
 if (num2==0)
 {
      throw DivideByZeroError ();
 }
 return (float) num1 / num2;
 
}

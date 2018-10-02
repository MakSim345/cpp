//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "div_error.h"

DivideByZeroError::DivideByZeroError() : 
    message("geLeHue Ha HoLb!\n")
{
 
}

void DivideByZeroError::printMesage() const 
{
    printf ("%s", message);
}

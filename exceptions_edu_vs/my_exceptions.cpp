//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "my_exceptions.h"
#include "div_error.h"

int throw_error::Run()
{
    std::cout << "Hello World!\n";
    throw  std::runtime_error("Something really bad happens!\n");
    return 0;
}

throw_error::throw_error() 
{
    int i = 0;
    // _ASSERT(i > 0);
    std::cout << "a=" << a << "\n";
}

my_exceptions::my_exceptions():
    num1(0),
    num2(0) 
{   
    std::cout << "my_exceptions - init\n";
}

void my_exceptions::run()
{   
    cout << "BBeguTe 4epe3 npo6eL gBa 4ucLa gLq geLeHuq:\n";
    cin >> num1 >> num2;  
    quotient();
}

float my_exceptions::quotient(/*int num1, int num2*/)
{
    if (num2==0)
    {
        // throw DivideByZeroError ();
        throw  std::runtime_error("ERROR: Divizion to zer0!\n");
    }
    return (float) num1 / num2; 
}

float my_exceptions::quotient2(/*int num1, int num2*/)
{
    if (num2==0)
    {
        throw DivideByZeroError();
    }
    return (float) num1 / num2;
}


void my_exceptions::init_alphabet(vector<string>& alphabet)
{
    
}

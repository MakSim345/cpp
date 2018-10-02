//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "my_exceptions.h"

int App::Run()
{
    std::cout << "Hello World!\n";
    throw  std::runtime_error("Something really bad happens!\n");
    return 0;
}

App::App() 
{
    int i = 0;
    // _ASSERT(i > 0);
    std::cout << "a=" << a << "\n";
}

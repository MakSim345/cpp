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

my_exceptions::my_exceptions()
{   
    std::cout << "my_exceptions - init\n";
}

void my_exceptions::run()
{
    for (int i = 0; i<25; i++)
    {
        int a=rand() % my_array.size();
        cout << " " << my_array[a];
        cout << " ";
    }
    cout << endl;
}

void my_exceptions::init_alphabet(vector<string>& alphabet)
{
    
}

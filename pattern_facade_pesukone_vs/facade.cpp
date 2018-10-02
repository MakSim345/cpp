#include "facade.h"

using namespace std;

MyFacade::MyFacade()
{
    std::cout << "Facade: constructor calling....\n";
}

MyFacade::~MyFacade()
{
    std::cout << "Facade: Good bye!\n";
}
    
int MyFacade::run()
{
    // cout << "Cube with side " << side << " is equal to " << calculation(side) << "\n";
    a.fun();
    b.fun();
    
    return 1;
}

#include "ToDo.h"

ToDo::ToDo()
{
    std::cout << "ToDo:: -Constructor- called\n";
}

ToDo::~ToDo()
{

    std::cout << "ToDo:: -Destructor- called\n";
}

int ToDo::run()
{
    std::cout << "ToDo:: -RUN- function called\n";
    return 0;
}

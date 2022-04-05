#include "thread_example.h"

void main()
try
{
    Sample();
}
catch (exception& err)
{
    cerr << err.what() << endl;
}

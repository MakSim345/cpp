#include <iostream>
#include <vector>
#include <numeric>
#include "trace_logger.h"
#include "linked_list.h"

using namespace std;

int main(int argc, char* pArgs[])
{    
    
    list_ssn * my_ssn = new list_ssn();
    my_ssn->run();
    system("PAUSE");
    return 0;
}

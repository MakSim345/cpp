#include "calc.h"

int add (std::string numbers)
{
    if (numbers.empty())
    {
        return 0;
    }
    
    int result;
    int _tellg;
    std::stringstream ss(numbers);
    ss >> result;
    std::cout << "result: " << result << "\n";
    // std::cout << "ss.tellg()    : " << ss.tellg() << "\n";
    std::cout << "numbers.size(): " << numbers.size() << "\n";    
    _tellg = ss.tellg();
    while (_tellg != numbers.size())
    {
        char delim;
        int next;
        ss >> delim;
        ss >> next;
        result += next;
        _tellg = ss.tellg();
    }   

    return result;
}

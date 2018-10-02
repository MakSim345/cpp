#include <iostream>
#include "utils.h"

using namespace std;

template <class superTypeT>
class Bucky
{
    superTypeT first, second;
public:
    Bucky(superTypeT a, superTypeT b) 
    {
        std::cout << "Bucky constructor" << std::endl; 
        first = a;
        second = b;
    }

    superTypeT bigger();
};

template <class superTypeT>
superTypeT Bucky<superTypeT>::bigger() 
{
    return (first>second?first:second);
}

template <class FIRST, class SECOND>
FIRST smaller(FIRST a, SECOND b)
{
    return (a<b?a:b);
}


int main()
{   
    // Bucky <float> *bucky_float;
    // bucky_float = new Bucky(12.5, 2.4);
    Bucky <float> bucky_float(12.5, 2.4);
    cout << "Float comparation: " << bucky_float.bigger() << endl;
    
    Bucky <int> bucky(67, 105);
    cout << "Int comparation: " << bucky.bigger() << endl;
    
    int x = 89;
    double y = 56.78;
    cout << "Universal comparation: " << smaller(x, y) << endl;

    system("PAUSE");
    
    return 1;
}




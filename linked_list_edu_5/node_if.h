#include "iostream"
using std::cout;
using std::cin;
using std::endl;

template <class super_class>
class node
{
public:
    super_class data;
    node<super_class>* next;

    node<super_class>(super_class val)
    {
        data = val;
        next = NULL;
    }
    
    node<super_class>()
    {
        next = NULL;
    }
    
};

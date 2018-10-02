//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "trash.h"

bool isAdult(Person &p)
{
    if (18 < p.age)
    {
        return true;
    }
    return false;
}

void checkDasha()
{
    Person dasha = {15, 160, 50, "Dasha", "Student"};    
    cout << sizeof(dasha) << endl;
    cout << dasha.name << " is ";
    if (!isAdult(dasha))
    {
        cout << "not ";
    }
    cout << "an adult\n";
}

class baseClassFoo 
{
private:
    int a;
    int b;

public:
    baseClassFoo(int x)
      :b(x)
      ,a(b) 
    {
     // NOP;
    }
    void dump() 
    {
        std::cout << "a=" << a << " b=" << b << std::endl;
    }
};



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

class A 
{
private:
    int a;
    int b;

public:
    A(int x)
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


//-------------------CLASS definition----------------
_my_template_class_t::_my_template_class_t()
{   
    system ("TITLE Phone book");
    system ("color 0A");
}

void _my_template_class_t::run()
{
    for (int i = 0; i<25; i++)
    {
        //int a=rand() % matrix_array.size();
        //cout << " " << matrix_array[a];
        cout << " ";
    }
    cout << endl;
}
//---------------END of CLASS Definition--------------

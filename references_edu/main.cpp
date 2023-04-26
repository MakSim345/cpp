#include <iostream>
#include <string>
#include "utils.h"
/*
* Cherno:
* https://www.youtube.com/watch?v=IzoFn3dfsPA&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=17
*/


inline float cube (const float s) {return s*s*s;}

using namespace std;

enum day {SUN, MON, TUE, WED, THU, FRI, SAT};

class Auto
{
public:
    static int gCounterM;

    Auto()
        :strAutoNameM("noname-")
    {
        gCounterM++;
        setAutoName("noname-");
        std::cout << "New Auto " << strAutoNameM << " created\n";
    }
   ~Auto() 
   {
       std::cout << strAutoNameM << ": deleted!\n";
   }

    void setAutoName(string new_name)
    {
        char str[12];
        int num = 3;
        sprintf(str, "%d", gCounterM); // str now contains "3"
        strAutoNameM = new_name + str;
        // std::cout << _auto_name << "\n";
        // printf ("my auto name = %s\n", this-> _auto_name);
    }
    
    std::string getAutoName() {return strAutoNameM;}

private:
    std::string strAutoNameM;

};

int Auto::gCounterM = 0;

void Increment(int &valueP)
{
    valueP++;
}

void testReferencesAndPointers()
{
    int a =  10;
    int &b = a;
    int *pointer = &a;

    cout << "a = " << a << "\n";
    cout << "Address of a = " << pointer << "\n";
    cout << "b = " << b << "\n";

    Increment(a);

    cout << "a = " << a << "\n";
    cout << "Address of a = " << pointer << "\n";
    cout << "b = " << b << "\n";

    a = 3004;
    cout << "\na set to: " << a << "\n\n";

    cout << "a = " << a << "\n";
    cout << "Address of a = " << pointer << "\n";
    cout << "Address of b = " << &b << "\n";
    cout << "b = " << b << "\n";
}

void showDay()
{
    day x = SUN;
    cout << "x = " << x << "\n";
    //++x;
    cout << "x = " << x << "\n";
}

Auto* makeAuto()
{
    Auto *_my_auto;
    _my_auto = new Auto();
    _my_auto->setAutoName("super_car");
    string _tmp = _my_auto->getAutoName();
    std::cout << "_auto_name: " << _tmp << "\n";
    // printf ("my auto name = %s\n", _my_auto->_name());
    // printf ("my auto name = %s\n", _tmp);
    return _my_auto;
}

struct big_data
{
    // Auto data[9999999];
       Auto data[1];
}; // big!

void do_something(big_data d)
{
    std::cout << "d[0]._name: " << d.data[0].getAutoName() << "\n";
    std::cout << "do_something - over\n";
}

int main()
{
   testReferencesAndPointers();
   // showDay();
   //Auto *_my_auto = makeAuto();
   //cout << "my auto name = " << _my_auto->_name() << "\n";
   // printf ("my auto name = %s\n", _my_auto->_name());
   //Auto *_my_auto;
   //_my_auto = new Auto();
    
    return 1;

    std::cout << "create big data...\n";
    big_data d;
    std::cout << "call do_something...: \n";
    do_something(d);
    std::cout << "END\n";

    // Auto *ptr = new Auto[100];
    // Auto data[2];
    //std::cout << "data[1]._name: " << data[1]._name() << "\n";

    return 1;
}


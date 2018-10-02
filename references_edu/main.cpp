#include <iostream>
#include <string>
#include "utils.h"

inline float cube (const float s) {return s*s*s;}

using namespace std;

enum day {SUN, MON, TUE, WED, THU, FRI, SAT};

class Auto
{
private:
    string _auto_name;

public:
    static int gCounter;

    Auto()
        :_auto_name("noname-")
    {
        gCounter++;
        set_name("noname-");
        std::cout << "New Auto " << _auto_name << " created\n";
    }
   ~Auto() 
   {
       std::cout << _auto_name << ": deleted!\n";
   }

    void set_name(string new_name)
    {
        char str[12];
        int num = 3;
        sprintf(str, "%d", gCounter); // str now contains "3"
        _auto_name = new_name + str;
        // std::cout << _auto_name << "\n";
        // printf ("my auto name = %s\n", this-> _auto_name);
    }
    string _name() {return _auto_name;}
};

int Auto::gCounter = 0;

void myPointers()
{
    int a =  10;
    int &b = a;
    int *pointer = &a;

    cout << "a = " << a << "\n";
    cout << "pointer to a = " << pointer << "\n";
    cout << "b = " << b << "\n";

    a = 3004;
    cout << "\na set to: " << a << "\n\n";

    cout << "a = " << a << "\n";
    cout << "pointer to a = " << pointer << "\n";
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
    _my_auto->set_name("super_car");
    string _tmp = _my_auto->_name();
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
    std::cout << "d[0]._name: " << d.data[0]._name() << "\n";
    std::cout << "do_something - over\n";
}

int main()
{
   // myPointers();
   // showDay();
   //Auto *_my_auto = makeAuto();
   //cout << "my auto name = " << _my_auto->_name() << "\n";
   // printf ("my auto name = %s\n", _my_auto->_name());
   //Auto *_my_auto;
   //_my_auto = new Auto();
    
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


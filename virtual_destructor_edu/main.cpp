#include <iostream>
#include "utils.h"
/*
"https://www.youtube.com/watch?v=jyaxGwOHFJ4"
*/

inline float cube (const float s) {return s*s*s;}

using namespace std;

class Base
{
 public:
    Base()
    {
        cout << "[o]Base constructor called." << endl;
    }
    // ~Base()
    virtual ~Base()
    {
        cout << "[x]Base destructor called." << endl;
    }
};

class Derived: public Base
{
 public:
    Derived()
    {
        cout << "[o]Derived constructor called." << endl;
    }

    ~Derived() override
    {
        cout << "[x]Derived destructor called." << endl;
    }
};

class Auto
{
 public:
    Auto() {cout << "*Auto constructor called." << endl;}
    ~Auto() {cout << "----Auto destructor called." << endl;}
};

void _my_swap(int* source, int* dest)
{
    printf ("_my_swap: source address 0x%X\n", source);
    printf ("_my_swap: source value %d\n", *source);
    int t = *source;
    *source = *dest;
    *dest = t;
}

void _my_swap_ref(int& source, int& dest)
{
    int t = source;
    source = dest;
    dest = t;
}

void show_delete()
{
    // [] operators in C++
    Auto *auto_ptr;
    auto_ptr = new Auto[3];
    delete [] auto_ptr;
}

struct Time
{
    int m;
    int h;
    int s;
};

typedef struct
{
    std::string _name;
    //int m;
    //int h;
    //int s;
    int ms;
} my_time;

void print_my_struct(my_time* _to_print)
{
    printf ("ms: %d\n", _to_print->ms);
    printf ("name: %s\n", _to_print->_name);
    // cout << "name:" << _to_print._name << endl;
    /*cout << "h:" << _to_print._name << endl;
    cout << "m:" << _to_print._name << endl;
    cout << "s:" << _to_print._name << endl;
    cout << "ms:" << _to_print._name << endl;   */
}

int main()
{
    // print_message();
    cout << "Main app start." << endl ;

    cout << "Create basePtr=new Derived():" << endl ;
    Base *basePtr;
    basePtr = new Derived();
    delete basePtr;// Note: undefined behaviour if no virtual!

    cout << "Create derivedPtr = new Derived():" << endl ;
    Derived *derivedPtr;
    derivedPtr = new Derived();
    delete derivedPtr;

    cout << "END." << endl ;
    return 1;

    int a = 12;
    int b = 99;
    printf ("Before swap: %d, %d\n", a, b);
    _my_swap(&a, &b);
    printf ("After swap: %d, %d\n", a, b);

    printf ("Before swap2: %d, %d\n", a, b);
    _my_swap_ref(a, b);
    printf ("After swap2: %d, %d\n", a, b);

    show_delete();

    my_time _mt;
    _mt.ms = 134;
    _mt._name = "134";
    printf ("name: %s\n", _mt._name);
    print_my_struct(&_mt);

    cout << "Main app end." << endl ;

    return 1;
}


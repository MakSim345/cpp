#include <iostream>
#include "utils.h"
/*
"https://www.youtube.com/watch?v=jyaxGwOHFJ4"
*/

class Base
{
 public:
    Base()
    {
        cout << "[o]Base - constructor called." << endl;
    }
    
    ~Base() {cout << "[x]Base - destructor called." << endl;}
    // virtual ~Base(){ cout << "[x]Base - destructor called." << endl;}
};

class Derived: public Base
{
 public:
    Derived()
    {
        cout << "[o]Derived constructor called." << endl;
    }

    // ~Derived() override
    ~Derived()
    {
        cout << "[x]Derived destructor called." << endl;
    }
};


int main()
{
    // print_message();
    cout << "Main app start." << endl ;

    cout << "Create basePtr=new Derived():" << endl ;
    Base *basePtr;
    basePtr = new Derived();
    delete basePtr; // Note: undefined behavior if no virtual!

    cout << "Create derivedPtr = new Derived():" << endl ;
    Derived *derivedPtr;
    derivedPtr = new Derived();
    delete derivedPtr;

    cout << "END." << endl ;
    system("PAUSE"); // wait for press any key in VS mode
    return 1;
}


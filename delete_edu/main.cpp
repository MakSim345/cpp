#include <iostream>
#include "utils.h"

using namespace std;

class Base
{
 public:
    Base() { cout << "-Base constructor called." << endl;}

 // protected:
    ~Base() {cout << "-Base destructor called." << endl;}
};

class Derived: public Base
{
 public:
    Derived(){cout << "*Derived constructor called." << endl;}
    ~Derived() { cout << "*Derived destructor called." << endl;}
};

class Auto
{
 public:
    Auto() {cout << "*Auto constructor called." << endl;}
    ~Auto() {cout << "----Auto destructor called." << endl;}
};

void show_delete()
{
    // [] operators in C++

    Auto *ptr_to_car;
    ptr_to_car = new Auto[3];
    delete [] ptr_to_car;

    // When we have allocated memory for array of objects like
    Auto *pa= new Auto[10]; //pointer to an array of 10 auto
    delete [] pa; // then to free memory equal to 10 auto:
}

void simple_delete()
{
    Auto *ptr_to_car;
    ptr_to_car = new Auto();
    // now to free the memory
    delete ptr_to_car;
}

void show_delete_2()
{
    // NOTE: One can free the memory even by "delete p";
    // but it will free only the first element memory.
    // You delete [] when you newed an array type, and delete when you didn't.
    // Examples:

    cout << "Function show_delete_2():" << endl ;
    typedef Auto auto_array[10];

    int *a = new int;
    int *b = new int[10];
    // Auto *c = new auto_array;
    Auto *c = new Auto[5];


    delete a;
    delete[] b;
    // delete[] c; // this is a must! even if the new-line didn't use [].
    delete c;
}

int main()
{
    // print_message();
    cout << "Main app start." << endl ;

    // show_delete();
    show_delete_2();

    cout << "Main app end." << endl ;

    return 1;
}


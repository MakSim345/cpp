#include <iostream>
#include "utils.h"

using namespace std;

class SomeClass
{
    int *ptr; // pointer to a memory allocation
public:

    SomeClass() //  конструктор
    {
        cout << "\nSomeClass: usual constructor called.\n";
    }

    SomeClass(const SomeClass &obj)
    {
        cout << "\nSomeClass: COPY constructor called\n";
    }

    ~SomeClass()
    {
        cout << "\nSomeClass: I am destroyer!!!!\n";
    }

    void printMe()
    {
        cout << "----Hi. My name is SomeClass.\n";
    }
};

// void funcShow(SomeClass &object)
void funcShow(SomeClass object)
{
    cout << "\nCall a function which takes object as a parameter\n";
}

SomeClass funcReturnObject()
{
    SomeClass object;
    cout <<   "\nCall a function which returns an object\n";
    return object;
}

int main()
{
    setlocale(LC_ALL,"rus");

    cout << "\n1 ~~~~~~~Create a object of a class";
    SomeClass obj1;

    cout << "\n2 ~~~~~~~Pass the object to function";
    funcShow(obj1);

    cout << "\n3 - 4 ~~~this function returns an object";
    SomeClass a = funcReturnObject();
    a.printMe();

    cout << "\n5 ~~~~~~~init an object at time of creation";
    SomeClass obj2 = obj1;

}


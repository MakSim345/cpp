#include "gen.h"
#include "deck.h"
// #include "IDGenerator.h"
// class IDGenerator;
//int add(int x, int y, int z);

using namespace std;

template<class T>
void swapVal(T obj1, T obj2)
{
    T temp = obj1;
    obj1 = obj2;
    obj2 = temp;
}

template<class superType>
void swapRef(superType &obj1, superType &obj2)
{
    cout << "called swapRef..." << endl;
    superType temp = obj1;
    obj1 = obj2;
    obj2 = temp;
}


int  squareByRefConst(const int& iRef)
{
    cout << "called squareByReference..." << endl;
    // iRef *= iRef;
    return iRef*iRef;
}

void squareByReference(int& iRef)
{
    cout << "called squareByReference..." << endl;
    iRef *= iRef;
}

void squareByPointer(int *iRef)
{
    cout << "called squareByPointer..." << endl;
    *iRef *= *iRef;
}

int add(int x, int &y, int z)
{
    return x + y + z;
}

int & retVal01()
{
    static int i = 100;
    return i;
}

void test_01()
{
    int z = 4;
    // cout << "3 + 4 + 5 = " << add(3, z, 5) << endl;

    cout << "before: z = "<< z << endl;
    squareByReference(z);
    cout << "after: z = "<< z << endl;

    cout << endl;

    int zz = 16;
    cout << "before: zz = "<< zz << endl;
    squareByPointer(&zz);
    cout << "after: zz = "<< zz << endl;

    cout << endl;

    int a = 100, b = 200;
    cout << "Value:" << endl;
    cout << "1: a = " << a << " b = " << b << endl;
    swapVal(a, b);
    cout << "2: a = " << a << " b = " << b << endl;

    float aRef = 10.19, bRef = 11.30;
    cout << "Value:" << endl;
    cout << "1: a = " << aRef << " b = " << bRef << endl;
    swapRef(aRef, bRef);
    cout << "2: a = " << aRef << " b = " << bRef << endl;
}

void test_02()
{
    cout << "1. Value: ";
    int& _my_val = retVal01();
    cout << _my_val << endl;
    _my_val++;
    cout << "2. Value: ";
    cout << _my_val << endl;
    cout << retVal01() << endl;
}

std::string* strRef()
{
    std::string _str_to_test;
    // Do cool things to or using str
    _str_to_test = "Return string by reference";
    return &_str_to_test;
}

std::string strValue()
{
    std::string _str_to_test;
    // Do cool things to or using str
    _str_to_test = "Return string by value";
    return _str_to_test;
}


std::string* strPtr()
{
    std::string* _str_to_test = new std::string("Return string pointer");
    return _str_to_test;
}

int main( int argc, char *argv[] )
{
    // srand (time(NULL));
    cout << "strRef() returns: " << strRef() << endl;
    cout << "strValue() returns: " << strValue() << endl;
    cout << "strPtr() returns: " << strPtr() << endl;
    return 0;
}



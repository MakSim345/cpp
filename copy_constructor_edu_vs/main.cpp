#include <iostream>
#include "utils.h"

/**
 * Check in video:
 * 2021-APR e-Spectre
 * https://www.youtube.com/watch?v=BvR1Pgzzr38 
*/

using namespace std;

class SomeClass
{
    int *ptr; // pointer to a memory allocation
public:

    SomeClass()
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



int testSomeClass()
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

    return 0;
}



class String
{
private:
    char *m_Buffer;
    unsigned int m_Size;
    
    // here we prevent copy in general
    // String (const String& otherP);

public:
    String(const char* stringP)
    {
        m_Size = strlen(stringP);
        m_Buffer = new char[m_Size+1]; // null character to add
        memcpy(m_Buffer, stringP, m_Size);
        m_Buffer[m_Size] = 0;
    }
    // use friend to give access to a private member m_Buffer:
    friend std::ostream& operator<<(std::ostream& streamP, const String& stringP);

    // as we use new keyword, needed to delete array in destructor:
    ~String()
    {
        delete [] m_Buffer;
    }

    char& operator [] (unsigned int indexP)
    {
        return m_Buffer[indexP];
    }

    String (const String& otherP)
        : m_Size (otherP.m_Size)
    {   
        m_Buffer = new char[m_Size+1]; // null character to add
        memcpy(m_Buffer, otherP.m_Buffer, m_Size+1); // rem: origin m_Buffer[m_Size] already has 0 as line end;
    }

};

// Function:
std::ostream& operator<<(std::ostream& streamP, const String& stringP)
{
    // in case use friend:
    streamP << stringP.m_Buffer;
    // streamP << stringP.GetBuffer();
    return streamP;
}

int main()
{
    String test_string_1 = "Cherno";
    String test_string_2 = test_string_1; // without copy constructor it is going to the same memory address 

    std::cout << test_string_1 << std::endl;
    std::cout << test_string_2 << std::endl; // allocate memory second time, and then in destructor delete[] will crash

    test_string_2[2] = 'a'; // test_string_2 not an array, need to redefine operator[] as separate function

    std::cout << test_string_1 << std::endl;
    std::cout << test_string_2 << std::endl; // allocate memory second time, and then in destructor delete[] will crash

    system("PAUSE");
    //system("pause>0");

    // std::cout << "\nPress ENTER to exit...\n";
    //cin.get();
}

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

struct Vector2
{
    float x, y;
    Vector2() :
        x(1.123), y(2.321) {}
};

class String
{
private:
    char* m_Buffer;
    unsigned int m_Size;

    // here we prevent copy in general
    // String (const String& otherP);

public:
    String(const char* stringP)
    {
        // check how long the String is:
        m_Size = strlen(stringP);

        // init the buffer array, note we are using "new", so need "delete" later:
        m_Buffer = new char[m_Size+1]; // null character to add

        // use memcopy to fill the buffer:
        memcpy(m_Buffer, stringP, m_Size);
        m_Buffer[m_Size] = 0;
    }

    // as we use new keyword, needed to delete array in destructor:
    ~String()
    {
        delete[] m_Buffer;
    }

    // to allow String modify as an array we need to overload "[]" operator:
    char& operator[] (unsigned int indexP)
    {
        return m_Buffer[indexP];
    }

    // The Copy Constructor.
    // need to allocate some new string array, for copy:
    String (const String& otherP)
        : m_Size (otherP.m_Size)
    {
        std::cout << "Copy Constructor called " << std::endl;
        m_Buffer = new char[m_Size+1]; // null character to add
        //note: origin m_Buffer[m_Size] already has 0 as line end;
        memcpy(m_Buffer, otherP.m_Buffer, m_Size+1);
    }
    // Note: if we do not need to copy this class, use follow Copy Constructor:
    // String (const String& otherP) = delete;

    // use friend to give access to a private member m_Buffer:
    friend std::ostream& operator<<(std::ostream& streamP, const String& stringP);
};

// Function overloading the operator "<<":
std::ostream& operator<<(std::ostream& streamP, const String& stringP)
{
    //1. in case use friend:
    streamP << stringP.m_Buffer;

    // 2. if not friend, we need to use a getter:
    // streamP << stringP.GetBuffer();
    return streamP;
}

void PrintString(const String& stringP)
{
    //1. note: if parameter stringP was not "const", we could change it:
    // stringP[2] = 'o';
    
    //2. note: "String&" is needed for prevent extra Copy Constructor calling!
    std::cout << stringP << std::endl;
}

void testMyStringsCrash()
{
    String test_string_1 = "Cherno";

    // The crash situation:
    // allocate memory second time, and then in destructor "delete[]" it will crash
    // without copy constructor it is going to the same memory address
    String test_string_2 = test_string_1;

    // Note: operator "<<" was overloaded for use in exact this class
    std::cout << "test_string_1: " << test_string_1 << std::endl;
    std::cout << "test_string_2: " << test_string_2 << std::endl;

    std::cout << "Replace char in test_string_2[2] to 'a': \n";

    // Note: operator "[]" was overloaded for use in exact this class
    // test_string_2 not an array, need to redefine operator[] as separate function
    test_string_2[2] = 'a';
    PrintString(test_string_1);
    PrintString(test_string_2);
    //std::cout << test_string_2 << std::endl;    
    //std::cout << test_string_1 << std::endl;
}

void testMyStrings()
{
    String test_string_1 = "Cherno";
    String test_string_2 = "Chirno";

    // Note: operator "<<" was overloaded for use in exact this class
    std::cout << "test_string_1: \n";
    std::cout << test_string_1 << std::endl;
    std::cout << "test_string_2: \n";
    std::cout << test_string_2 << std::endl; // allocate memory second time, and then in destructor delete[] will crash

    std::cout << "Replace char in test_string_2[2] to 'a': \n";
    test_string_2[2] = 'a'; // test_string_2 not an array, need to redefine operator[] as separate function
    std::cout << test_string_2 << std::endl; // allocate memory second time, and then in destructor delete[] will crash

    std::cout << "test_string_1: \n";
    std::cout << test_string_1 << std::endl;
}

void testMyVectors()
{
    Vector2* a = new Vector2();
    std::cout << "Vector2 a has not been init:\n ";
    std::cout << "a->x = " << a->x << ", a->y = " << a->y << "\n";

    Vector2* b = a;
    std::cout << "Vector2 b has not been init:\n ";
    std::cout << "b->x = " << b->x << ", b->y = " << b->y << "\n";

    b->x = 4.567;
    std::cout << "a->x = " << a->x << ", a->y = " << a->y << "\n";
    std::cout << "b->x = " << b->x << ", b->y = " << b->y << "\n";
}


int main()
{
    testMyStringsCrash();
    system("PAUSE");
}

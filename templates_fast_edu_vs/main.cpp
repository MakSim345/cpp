#include <iostream>
#include <string>
#include "utils.h"

/**
 * Check in video:
 * https://www.youtube.com/watch?v=I-hZkUa9mIs
 * https://www.youtube.com/watch?v=W0aoAm6eYSk
*/

using namespace std;

template <class superTypeT>
class Bucky
{
    superTypeT first, second;
public:
    Bucky(superTypeT a, superTypeT b) 
    {
        std::cout << "Bucky constructor" << std::endl; 
        first = a;
        second = b;
    }

    superTypeT bigger();
};


template <class T, class U>
class Person
{
public:
    T height;
    U weight;
    static int numOfPeople;

    Person(T h, U w)
    {
        height = h;
        weight = w;
        numOfPeople++;
    }

    void getData()
    {
        std::cout << "Height: " << height << "and Weight: " << weight << "\n";
    }
};

template <typename T, typename U> int Person <T, U>::numOfPeople;


class String
{
private:
    char *m_Buffer;
    unsigned int m_Size;

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
};

// Function:
std::ostream& operator<<(std::ostream& streamP, const String& stringP)
{
    // in case use friend:
    streamP << stringP.m_Buffer;
    // streamP << stringP.GetBuffer();
    return streamP;
}

template <typename T, int ARRAY_SIZE_N>
class Array
{
private:
    T mArray[ARRAY_SIZE_N];

public:
    T GetSize() const {return ARRAY_SIZE_N;}
};

template <class superTypeT>
superTypeT Bucky<superTypeT>::bigger() 
{
    return (first>second?first:second);
}

template <class FIRST, class SECOND>
FIRST smaller(FIRST a, SECOND b)
{
    return (a<b?a:b);
}

// template <class T> // REM: class is same as typename!
template <typename T>
void Print (T valueP)
{
    std::cout << valueP << std::endl;
}

// REM: template does not exist before it has been used
template <typename T>
void Print_with_error (T valueP)
{
    std::cout << value << std::endl; // incorrect parameter value used!
}
/*
void Print (int valueP)
{
    std::cout << valueP << std::endl;
}

void Print (std::string valueP)
{
    std::cout << valueP << std::endl;
}
*/


template <typename T>
void Times2 (T val)
{
    std::cout << val << " * 2 = " << val * 2 << "\n";
}

template <typename T>
T Add (T val, T val2)
{
    return val + val2;
}

template <typename T>
T Max (T val, T val2)
{
    return (val < val2) ? val2 : val;
}

int main()
{   
    // Bucky <float> *bucky_float;
    Bucky <float> *bucky_float;
    bucky_float = new Bucky<float>(12.5, 2.4);

    Times2(5);
    Times2(4.9);
    
    std::cout << "5 + 4 = " << Add(5,4) << "\n";
    std::cout << "5.5 + 4.6 = " << Add(5.5, 4.6) << "\n";
    std::cout << "Max of 4 or 8 = " << Max(4, 8) << "\n";
    std::cout << "Max of A or B = " << Max('A', 'B') << "\n";
    std::cout << "Max of Dog or Cat = " << Max("Dog", "Cat") << "\n";

    Person <int, int> mikeTyson(67, 105);
    mikeTyson.getData();
    std::cout << "Number of people: " << mikeTyson.numOfPeople << "\n";

    String test_string = "Cherno";
    std::cout << test_string << std::endl;    
    
    //Bucky <float> bucky_float(12.5, 2.4);
    //cout << "Float comparation: " << bucky_float.bigger() << endl;
    
    Bucky <int> bucky(67, 105);
    cout << "Int comparation: " << bucky.bigger() << endl;
    
    int x = 89;
    double y = 56.78;
    cout << "Universal comparation: " << smaller(x, y) << endl;

    Print(x); // parameter is implicit
    Print <int>(x); // same as above
    Print("->hello");
    Print(y);

    Array <int, 50> array;
    Print (array.GetSize());
    // Array *array = new Array <5>;
    // Print (array->GetSize());

    system("PAUSE");
    //system("pause>0");
    
    // std::cout << "\nPress ENTER to exit...\n";
    //cin.get();

    return 1;
}




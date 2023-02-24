/*
C++ Structures for beginners (explained in 30 minutes)
https://www.youtube.com/watch?v=9j5KkOC_goQ
*/

// #include <stdio>
#include <thread>
#include <atomic>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

static std::atomic<int> av;
static int gv;

using String = std::string;

class Entity
{
public:
    Entity() : sNameM("Unknown") {};
    Entity(const String& nameP) : sNameM(nameP) {};

    // ~Entity();
    const String& GetName() const { return sNameM; }

private:
    String sNameM;
};

void hello()
{
    std::cout <<  "Hello world, I'm a thread!" << std::endl;
}

int GetRandom(int maxP)
{
    static bool isFirstTime = true;
    if (isFirstTime)
    {
        srand(time(NULL));
        isFirstTime = false;
    }
    auto retVal = rand() % maxP;
    return retVal;
}
struct Smartphone
{
    std::string name;
    int storageSpace;
    std::string color;
    float priceInUsd;
};

void printSmartPhoneInfo(const Smartphone& smartP)
{
    std::cout << "SmartPhone name: " << smartP.name << std::endl;
    std::cout << "SmartPhone memory: " << smartP.storageSpace << " GB" << std::endl;
    std::cout << "SmartPhone color: " << smartP.color << std::endl;
    std::cout << "SmartPhone price: " << smartP.priceInUsd << " USD" << std::endl;

    // smartP.storageSpace = 23;
}

struct Person
{
    std::string name;
    int age;
    Smartphone smart;
};

void printPersonInfo(Person& personP)
{
    std::cout << "Person name: " << personP.name << std::endl;
    std::cout << "Person age: " << personP.age << std::endl;
    printSmartPhoneInfo(personP.smart);
}

int main()
{
    Smartphone mySmart;
    mySmart.name = "Samsung Galaxy G20+";
    mySmart.storageSpace = 128;
    mySmart.color = "Gray";
    mySmart.priceInUsd = 999.99;
    
    Smartphone mySmart2;
    mySmart2.name = "iPhone 12";
    mySmart2.storageSpace = 64;
    mySmart2.color = "Pink";
    mySmart2.priceInUsd = 1999.90;
    
    // printSmartPhoneInfo(mySmart);

    Person p;
    p.name = "Saldina";
    p.age = 26;
    p.smart = mySmart2;

    printPersonInfo(p);

    /*
    for (auto i = 0; i < 10; i++)
    {
        cout << "GetRandom: " << GetRandom(9999) << endl;
    }
    */
    system("PAUSE");
    return 0;
}

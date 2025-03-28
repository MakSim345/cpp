#include "gen.h"
#include "person.h"


void printSmartPhoneInfo(const Smartphone& smartP)
{
    std::cout << "SmartPhone name: " << smartP.name << std::endl;
    std::cout << "SmartPhone memory: " << smartP.storageSpace << " GB" << std::endl;
    std::cout << "SmartPhone color: " << smartP.color << std::endl;
    std::cout << "SmartPhone price: " << smartP.priceInUsd << " USD" << std::endl;

    // smartP.storageSpace = 23;
}

void printPersonInfo(Person& personP)
{
    std::cout << "Person name: " << personP.name << std::endl;
    std::cout << "Person age: " << personP.age << std::endl;
    printSmartPhoneInfo(personP.smart);
}

void testPersonMobile()
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
}
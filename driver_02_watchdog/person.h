#include "gen.h"

struct Smartphone
{
    std::string name;
    int storageSpace;
    std::string color;
    float priceInUsd;
};

struct Person
{
    std::string name;
    int age;
    Smartphone smart;
};


void printSmartPhoneInfo(const Smartphone& smartP);
void printPersonInfo(Person& personP);
void testPersonMobile();
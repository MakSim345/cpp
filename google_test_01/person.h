#pragma once

#include "gen.h"

class Person
{
public:
    Person();
    ~Person();
    string getName();
    void setAge(int pAge);
    void setName(string pName);
    int getAge();
    
private:
    string nameM; 
    int ageM;
};


/*
// For unittests:

TEST(Person, testNameMethods)
{
    string name = "AJ O. Alves";
    Person* pers = new Person();
    pers->setName(name);

    EXPECT_EQ(pers->getName(), name);
}

TEST(Person, testAgeMethods)
{
    int age = 22;
    Person* pers = new Person();
    pers->setAge(age);

    EXPECT_EQ(pers->getAge(), age);
}
*/


#pragma once
#include "Address.h"
#include "gen.h"

class Person
{
public:
    Person() : address(nullptr) {}

    Person(const string& aName, int aAge) : 
         name(aName),
         age(aAge),
         address(new Address( "unknown street", "unknown city" ))
    {
        cout << "Person's constructor..." << endl;
    }
    
     // as we derived it in Student, destructor must be virtual:
    virtual ~Person() 
    {
        cout << "Person " <<  name << " record destructed" << endl;
    }

    void setName(const string& aName)
    {
        name = aName;
    }

    string getName() const 
    {
        return name;
    }

    void setAge(int aAge)
    {
        age = aAge;
    }

    int getAge() const
    {
        return age;
    }

    virtual void printData() const
    {
        cout << "Name: " << name << "\nAge: " << age << endl;
    }

private:
    string name;
    int age;
    Address* address; // TODO later
};
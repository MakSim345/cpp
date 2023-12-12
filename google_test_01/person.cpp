#include "person.h"

Person::Person()
{
    std::cout << "Hello! New Person appears\n";
}
Person::~Person()
{
    std::cout << "Person: Good bye!\n";
}
    
void Person::setName(string pName) 
{
    this->nameM=pName;
}

string Person::getName() 
{
    return this->nameM;
}

void Person::setAge(int pAge)
{
    this->ageM = pAge;
}

int Person::getAge()
{
    return this->ageM;
}

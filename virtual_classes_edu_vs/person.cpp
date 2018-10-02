#include "gen.h"
#include "person.h"

//============================================================
//
// 2011
//
//============================================================

Person::Person()
{
    cout << "Person constructor..... " << "\n";
}

Person::~Person()
{
    cout << "Person destructor..... " << "\n";
}

Student::Student():
isStudent(true)
{
    cout << "Student constructor..... " << "\n";
}

Student::~Student()
{
    cout << "Student destructor..... " << "\n";
}

bool Student::amIStudent()
{
    return isStudent;
}   
//============================================================
//
// Description:
// <purpose of this file>
//============================================================

#include "Person.h"

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


bool validateStudent(Student _person_to_check)
{
    return _person_to_check.amIStudent();
}


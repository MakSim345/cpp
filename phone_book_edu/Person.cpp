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


bool validateStudent(Student s)
{
    return s.amIStudent();
}

Window::Window()
    :_name("my_window")
{}

Window::~Window()
{}

std::string Window::name() const
{
    return _name;
}

void Window::display() const
{
    cout << "---------------" << "\n";
    cout << "Window - SHOW! " << "\n";
    cout << "---------------" << "\n";
}


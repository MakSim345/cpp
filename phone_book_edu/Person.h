#ifndef _PERSON_H_
#define _PERSON_H_
//============================================================
//
// Description:
//============================================================
#include "gen.h" 

class Person
{
public:
    Person();
    virtual ~Person();
    
private:
    std::string name;
    std::string address;

};


class Student: public Person
//class Student
{
public:
    Student();
    ~Student();

    bool amIStudent();
    
private:
    std::string schoolName;
    std::string schoolAddress;
    bool isStudent;
};


bool validateStudent(Student s);

class Window
{
public:
    Window();
    ~Window();

    std::string name() const;
    virtual void display() const;

private:
    std::string _name;
};


#endif

#ifndef _PERSON_H_
#define _PERSON_H_

#include "gen.h"

class Person
{
public:
    Person(const string sName, const string sEmail, const int iAge)
         :m_sName(sName)
         ,m_sEmail(sEmail)
         ,m_iAge(iAge)
    {
        ;
    }
    
    // default constructor :
    Person (): m_iAge(0) {};
    
    // copy constructor:
    Person (const Person &p):
        m_sName (p.m_sName), m_sEmail(p.m_sEmail), m_iAge(p.m_iAge) {};

   ~Person(){}

    string GetName() const {return m_sName; };
    string GetEmail() const {return m_sEmail;};
    int GetAge() const {return m_iAge;};

private:
    string m_sName;
    string m_sEmail;
    int m_iAge;
};


#endif

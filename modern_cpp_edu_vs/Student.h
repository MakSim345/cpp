#pragma once
#include "Address.h"
#include "Person.h"

#include "gen.h"

class Student : public Person 
{
public:
	Student();
	Student(string aName, int aAge, int aCreditPoints, string aStudentId) 
		: Person(aName, aAge), creditPoints(aCreditPoints), studentID(aStudentId) {}
	~Student() {
		cout << "Student's destructor " << endl;
	}

	int getCreditPoints() const
    {
		return creditPoints;
	}
    	
    void addCreditPoints(int aPoints)
    {
		creditPoints += aPoints;
	}
	
    string getStudentId() const 
    {
		return studentID;
	}
	
    void printData() const   override 
    {
		Person::printData();
		cout << "Student ID: " << studentID << endl;
		cout << "Credit points: " << creditPoints << endl;
	}

private:
	int creditPoints;
	string studentID;
};



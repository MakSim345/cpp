#include <string>
#include <iostream>
#include <vector>
using namespace std;

// This is the exercise base code for Modern C++ training
// The code has many things and bugs to correct and TODOs to make (as a first refresher exercise)

class Address 
{
public:
	Address() {}
	
    Address(string aStreet, string aCity) : street(aStreet), city(aCity) {}
	
    ~Address()
    {
		cout << "Destructing Address object" << endl;
	}
	
    void printData()
    {
		cout << street << " " << city << endl;
	}

private:
	string street;
	string city;
};

class Person 
{
public:
	Person() {}
	Person(string aName, int aAge) : name(aName), age(aAge), address( new Address( "unknown street", "unknown city" ))
    {
		cout << "Person's constructor..." << endl;
	}
	~Person() 
    {
		cout << "Person " <<  name << " destructed" << endl;
	}
	
    void setName(string aName)
    {
		name = aName;
	}
	
    string getName() 
    {
		return name;
	}
	
    void setAge(int aAge)
    {
		age = aAge;
	}
	
    int getAge()
    {
		return age;
	}
	
    void printData() 
    {
		cout << "Name: " << name << "\nAge: " << age << endl;
	}

private:
	string name;
	int age;
	Address* address; // TODO later
};

class Student : public Person {
public:
	Student();
	Student(string aName, int aAge, int aCreditPoints, string aStudentId) 
		: Person(aName, aAge), creditPoints(aCreditPoints), studentID(aStudentId) {}
	~Student() {
		cout << "Student's destructor " << endl;
	}

	int getCreditPoints() {
		return creditPoints;
	}
	void addCreditPoints(int aPoints) {
		creditPoints += aPoints;
	}
	string getStudentId() {
		return studentID;
	}
	void printData() {
		Person::printData();
		cout << "Student ID: " << studentID << endl;
		cout << "Credit points: " << creditPoints << endl;
	}

private:
	int creditPoints;
	string studentID;
};

int main() 
{
	vector<Person*> persons;
	persons.push_back(new Person("Ville", 20));
	persons.push_back(new Person("Marja", 25));
	persons.push_back(new Person("Maija", 19));
	persons.push_back(new Student("Kalle", 20, 0, "xxxyyy"));

	for (vector<Person*>::iterator& it = persons.begin(); it != persons.end(); ++it)
    {
		(*it)->printData();
	}

	system("pause");
	return EXIT_SUCCESS;
}





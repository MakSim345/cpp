#ifndef _BASE_H_
#define _BASE_H_

#include "gen.h"

class Cat
{
public:
    virtual ~Cat() {sayGoodBye();} // if this is not virtual, only this will be called
    void AskForFood() const
    {
        speak();
        eat();
    }
    virtual void speak() const {std::cout << " Meow! " << std::endl;}
    virtual void eat()   const {std::cout << " *yami-yami* " << std::endl;}
    virtual void sayGoodBye() const {std::cout << " Meow-meow! " << std::endl;}
};

class CheshireCat : public Cat
{
public:
    ~CheshireCat() {sayGoodBye();}
    virtual void speak() const {std::cout << " WTF! Where is my milk? =)" << std::endl;}
    // virtual void eat()   const {std::cout << " *yami-yami* " << std::endl;}
    virtual void sayGoodBye() const {std::cout << " Bye-Bye! " << std::endl;}
};


class Clock
{
public:
    // virtual void print() const = 0;
    
    // void print()
    virtual void print() const
    {
        //LOG_TRACE;
        std::cout << "Clock!" << std::endl;
    }
};

class Alarm: public Clock
{
public:
    virtual void print() const
    {
        //LOG_TRACE;
        std::cout << "Alarm!" << std::endl;
    }
};

//---------------------------------------------------
class baseClass
{
public:
    baseClass()  {}
    ~baseClass() {}

    virtual void who()
    {
        std::cout << "I am base\n";
    }
};

class firstDerivedClass : public baseClass
{
public:
    firstDerivedClass() {}
    /*void who ()
    {
        std::cout << "I am first derivation\n";
    }*/
};

class secondDerivedClass : public baseClass
{
public:
    void who ()
    {
        std::cout << "I am second derivation\n";
    }
};



using namespace std;
class mathBaseClass
{
public:
    // REM: if base_foo was not virtual, derived class will call this one, not his own base_foo!
    virtual int base_foo(const int &d)
    //int base_foo(const int &d)
    {
        std::cout << "MyBase: call f()\n";
        return 2*d;
    }

    int CallFunction(const int &d)
    {
        std::cout << "MyBase: CallFunction()\n";
        return base_foo(d) + 1;
    }
};

class mathDerivedClass: public mathBaseClass
{
public:
    int base_foo(const int &d)
    {
        std::cout << "Derived: call f()\n";
        return d*d;
    }
};

#endif

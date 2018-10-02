#include <conio.h>
#include <iostream>
#include "utils.h"

using namespace std;

#define USE_VIRTUAL

class employee
{
public:
#ifdef USE_VIRTUAL
    virtual int salary() { cout << "BASE: salary called." << endl; return 1;}
    virtual int bonus() { cout << "BASE: bonus called." << endl; return 1;}
#else
    int salary() { cout << "BASE: salary called." << endl; return 1;}
    int bonus() { cout << "BASE: bonus called." << endl; return 1;}
#endif
};

class manager : public employee
{
public:
#ifdef USE_VIRTUAL
    virtual int salary() { cout << "MNGR: salary called." << endl; return 1;}
#else
    int salary() { cout << "MNGR: salary called." << endl; return 1;}
#endif
};

class programmer : public employee
{
public:
#ifdef USE_VIRTUAL
    virtual int salary() { cout << "PROG: salary called." << endl; return 1;}
    virtual int bonus()  { cout << "PROG: bonus called." << endl; return 1;}
#else
    int salary() { cout << "PROG: salary called." << endl; return 1;}
    int bonus()  { cout << "PROG: bonus called." << endl; return 1;}
#endif
};

void payroll( employee *pe )
{
   pe->salary();
   pe->bonus();
}


class Clock
{
public:
    Clock() { cout << "Clock constructor called." << endl;}
#ifdef USE_VIRTUAL    
    virtual void print() const { cout << "Clock!" << endl; }
#else
    void print() const { cout << "Clock!" << endl; }
#endif    
};

class Alarm: public Clock
{
public:
    Alarm() { cout << "Alarm constructor called." << endl;}
    void print() const { cout << "Alarm!" << endl; }
};

// function accept Clock as a parameter, so all derived
// classes are ok as well.
void settime(Clock &d)
{ 
    d.print(); 
}

void test_manager()
{
    manager *mngr = new manager();
    payroll(mngr);
}

void test_clock()
{
    cout << "---Create Clock:" << endl;
    Clock _clock;
    settime(_clock);
    cout << "---Create Alarm:" << endl;
    Alarm _alarm;
    settime(_alarm);
    Clock *_pClock = &_clock;
    _pClock->print();
    cout << "set _pClock to Alarm:" << endl;
    _pClock = &_alarm;
    _pClock->print();
    int *pnValue = new int;
}

int main()
{
    cout << "APP start:" << endl;

    test_clock();

    cout << "APP END:" << endl;
    // getch();
}



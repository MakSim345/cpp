#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <ctime>
// #include "checkedcast.h"

using namespace std;

class Security
{
protected:
    enum { BASEID = 0};

public: 
    virtual ~Security();
    virtual bool isA(int id) {return (id == BASEID);}   
};


class Stock : public Security
{
typedef Security Super;
protected:
    enum {OFFSET=1, TYPEID=OFFSET + BASEID};
public:
    bool isA(int id) {return id == BASEID || Super::isA(id);}
    Stock();
    ~Stock();
    
};

int main()
{

    // vector <Security*> portfolio;
    int x = 65534;
    cout << "x=" << x << endl;
    signed short y = static_cast <signed short> (x);
    cout << "y=" << y << endl;
    
    int *p = new int;
    cout << "new p =" << p << endl;
    cout << "new *p=" << *p << endl;

    p = &x;
    cout << "&x = p =" << p << endl;
    cout << "&x = *p=" << *p << endl;
    
    *p = 2;
    cout << "p=" << p << endl;
    cout << "*p=" << *p << endl;
    cout << "x=" << x << endl;

    return 1;
}

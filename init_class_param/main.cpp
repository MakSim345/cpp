#include <iostream>
// #include "utils.h"

/*
REM: improper list of parameters in the class definition 
     cause undefined behavior
*/

using namespace std;

class ToTest
{
private:
    int data;

public:
    ToTest (int x)
    {
        std::cout << "ToTest (int x): x= " << x << "\n";
        data = x;
    }

    ToTest (ToTest& x)
    {
        std::cout << "ToTest (ToTest& x): x.data= " << x.data << "\n";
        data = x.data;
    }
    
    int dump ()
    {
        return data;
    }

    ~ToTest ()
    {
        std::cout << "~ToTest (): x.data= " << this->data << "\n";        
    }

};


class Base
{
public:
    virtual ~Base () {};
        
    virtual void dump () = 0;
};

class WrongInit : public Base
{
private:
    ToTest a;
    ToTest b;
public:
    WrongInit (int x) : 
        b(x), 
        a(b)
        { /* constructor body*/}
    void dump () 
    {
        std::cout << "a=" << a.dump() << " b=" << b.dump() << "\n";
    }    
};

class RightInit : public Base
{
private:
    int b;
    int a;    
public:
    RightInit (int x) : 
        b(x), 
        a(b)
        { /* constructor body*/}
    void dump () 
    {
        std::cout << "a=" << a << " b=" << b << "\n";
    }    
};

int main()
{
    //WrongInit w (42);
    //w.dump();
    //RightInit r (42);
    //r.dump();
    int x = 2;
    int y = 22;
    if (x == y) 
    {
        ToTest p(x); 
        p.dump();       
    }
    else
    {
       ToTest* p;
       p = new ToTest(345);
       p->dump();
       delete p;
    }

    return 0;
}


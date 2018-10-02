#ifndef _MY_EXCEPTIONS_H_
#define _MY_EXCEPTIONS_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

class App
{
public:
    App(int x)
      :b(x)
      ,a(b) 
    {
     // NOP;
    }
    App(); 
    int Run();

    void dump() 
    {
        std::cout << "a=" << a << " b=" << b << std::endl;
    }

private:
    int a;
    int b;

};

class my_exceptions
{
public:    
    my_exceptions();
    ~my_exceptions();
    
    void run();
        
private:    
    void init_alphabet(vector<string>& array_alphabet);
    vector <string> my_array;
};


#endif

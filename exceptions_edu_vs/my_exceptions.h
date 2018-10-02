#ifndef _MY_EXCEPTIONS_H_
#define _MY_EXCEPTIONS_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

class throw_error
{
public:
    throw_error(int x)
      :b(x)
      ,a(b) 
    {
     // NOP;
    }
    throw_error(); 
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
    float quotient();
    float quotient2();
    vector <string> my_array;
    int num1;
    int num2;    
};


class Exp: public std::exception
{
public:
    Exp();
    ~Exp();    
    // void run();

private:
    int num3;
    int num4;
};
#endif

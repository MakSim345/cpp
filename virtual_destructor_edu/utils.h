#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
using namespace std;

void print_message();

struct Time
{
    int m;
    int h;
    int s;
};

typedef struct
{
    std::string _name;
    //int m;
    //int h;
    //int s;
    int ms;
} my_time;

class Auto
{
public:
    Auto() { cout << "*Auto constructor called." << endl; }
    ~Auto() { cout << "----Auto destructor called." << endl; }
};
void _my_swap(int* source, int* dest);
void _my_swap_ref(int& source, int& dest);
void show_delete();
void print_my_struct(my_time* _to_print);

#endif


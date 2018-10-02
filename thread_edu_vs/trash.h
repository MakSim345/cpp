#ifndef _TRASH_H_
#define _TRASH_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

struct Person
{
    int age;
    int height;
    int weight;

    string name;
    string job;
};

bool isAdult(Person &p);
void checkDasha();
int produceRND();

class _my_template_class_t
{
public:    
    _my_template_class_t();
    ~_my_template_class_t();
    
    void run();
private:    
    vector <string> main_array;    
};


#endif

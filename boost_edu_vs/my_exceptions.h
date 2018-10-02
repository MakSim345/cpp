#ifndef _MY_EXCEPTIONS_H_
#define _MY_EXCEPTIONS_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"
#include "printHex.h"

class my_exceptions
{
public:    
    my_exceptions();
    ~my_exceptions();
    
    void run_matrix();
        
private:    
    void init_alphabet(vector<string>& array_alphabet);
    vector <string> my_array;    
};

#endif

#ifndef _MY_MATRIX_H_
#define _MY_MATRIX_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

class my_matrix
{
public:    
    my_matrix();
    ~my_matrix();
    
    void run_matrix();
        
private:
    void my_matrix::init_alphabet();
    void my_matrix::init_alphabet(vector<string>& array_alphabet);
    vector <string> matrix_array;
    
};


#endif

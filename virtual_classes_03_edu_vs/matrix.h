#ifndef _MY_EXCEPTIONS_H_
#define _MY_EXCEPTIONS_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

class matrix
{
public:    
    matrix();
    ~matrix();
    
    void run_matrix();
        
private:    
    // void init_alphabet(vector<string>& array_alphabet);
    void init_alphabet();
    vector <string> matrix_array;    
};

#endif

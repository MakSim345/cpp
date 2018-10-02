#pragma once
#include "gen.h"

class PassGenerator
{
public:
    PassGenerator();
    ~PassGenerator();

    int genRnd(int max);
    string genPass(int length); 
    void printResult();

protected:
    void init_alphabet(); 
    string _result_pass;

    vector<string> alphabet;
};
#ifndef _PASS_H_
#define _PASS_H_

#include "gen.h"

class Pass
{
public:
    Pass();
    ~Pass();

    void test_fun_01();
    void factorial();

    int genRnd(int max);
    string run(int length);

private:
    void init();
    vector<string> get_alphabet();
    vector<string> letters;
};

#endif


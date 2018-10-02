#ifndef _FIZZ_BUZZ_H_
#define _FIZZ_BUZZ_H_

#include "gen.h"

class fizz_buzz
{
public:
    fizz_buzz();
    ~fizz_buzz();

    void Run();

private:
    int nMaxVal;
    bool is_printed;
    bool div_three(int val);
    bool div_five (int val);
    void alg_one();
    void alg_two();
    void alg_three();

};

#endif


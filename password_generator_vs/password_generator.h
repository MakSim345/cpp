#ifndef _PASSWORD_GENERATOR_H
#define _PASSWORD_GENERATOR_H
/*********************************************************************

  password_generator.cpp
  01.10.2011 Initial coding YS 
  
**********************************************************************/
#include "gen.h"

#include "password_generator.h"

using namespace std;

class PassGenerator
{
public:
    PassGenerator();
    ~PassGenerator();

    int genRnd(int max);
    string genPass(int length); 
    void printResult();

protected:
    void initAlphabet(); 
    string strResultPassM;

    vector<string> alphabet;
};

#endif
 

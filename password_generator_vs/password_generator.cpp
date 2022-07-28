/*********************************************************************

  password_generator.cpp
  01.10.2011 Initial coding YS 
  
**********************************************************************/
#include "password_generator.h"

PassGenerator::PassGenerator()
    : strResultPassM("")
{   
    initAlphabet();
    srand((unsigned)time(0));
    rand();
}

PassGenerator::~PassGenerator()
{
    
}

void PassGenerator::printResult()
{
    cout << strResultPassM << endl; 
    cout << endl; 
}

int PassGenerator::genRnd(int max)
{
    return rand() % max;
}

string PassGenerator::genPass(const int passLengthP)
{    
    strResultPassM = "";
    for (int i = 0; i < passLengthP; ++i)
    {
        strResultPassM += alphabet[genRnd(alphabet.size())];
    }

    return strResultPassM;
}
 
void PassGenerator::initAlphabet()
{
    alphabet.push_back("q");
    alphabet.push_back("w");
    alphabet.push_back("e");
    alphabet.push_back("r");
    alphabet.push_back("t");
    alphabet.push_back("y");
    alphabet.push_back("u");
    alphabet.push_back("i");
    alphabet.push_back("o");
    alphabet.push_back("p");
    alphabet.push_back("a");
    alphabet.push_back("s");
    alphabet.push_back("d");
    alphabet.push_back("f");
    alphabet.push_back("g");
    alphabet.push_back("h");
    alphabet.push_back("j");
    alphabet.push_back("k");
    alphabet.push_back("l");
    alphabet.push_back("z");
    alphabet.push_back("x");
    alphabet.push_back("c");
    alphabet.push_back("v");
    alphabet.push_back("b");
    alphabet.push_back("n");
    alphabet.push_back("m");
    
    alphabet.push_back("Q");
    alphabet.push_back("W");
    alphabet.push_back("E");
    alphabet.push_back("R");
    alphabet.push_back("T");
    alphabet.push_back("Y");
    alphabet.push_back("U");
    alphabet.push_back("I");
    alphabet.push_back("O");
    alphabet.push_back("P");
    alphabet.push_back("A");
    alphabet.push_back("S");
    alphabet.push_back("D");
    alphabet.push_back("F");
    alphabet.push_back("G");
    alphabet.push_back("H");
    alphabet.push_back("J");
    alphabet.push_back("K");
    alphabet.push_back("L");
    alphabet.push_back("Z");
    alphabet.push_back("X");
    alphabet.push_back("C");
    alphabet.push_back("V");
    alphabet.push_back("B");
    alphabet.push_back("N");
    alphabet.push_back("M");
    // digits:
    alphabet.push_back("0");
    alphabet.push_back("1");
    alphabet.push_back("2");
    alphabet.push_back("3");
    alphabet.push_back("4");
    alphabet.push_back("5");
    alphabet.push_back("6");
    alphabet.push_back("7");
    alphabet.push_back("8");
    alphabet.push_back("9");
    alphabet.push_back("_");
    alphabet.push_back("-");
    alphabet.push_back("$");
    /*
    alphabet.push_back("@");
    alphabet.push_back("%");
    alphabet.push_back("#");
    */

    // return alphabet;
}



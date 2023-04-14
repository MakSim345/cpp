#include "password_generator.h"

PassGenerator::PassGenerator()
    : _result_pass("")
{   
    init_alphabet();
    srand((unsigned)time(0));
    rand();
}

PassGenerator::~PassGenerator()
{
    
}

void PassGenerator::printResult()
{
    // cout << genRnd(100) << endl;

    cout << _result_pass << endl; 
    cout << endl; 
}

int PassGenerator::genRnd(int max)
{
    return rand() % max;
}

string PassGenerator::genPass(int length)
{    
    _result_pass = "";
    for (int i = 0; i < length; ++i)
    {
        _result_pass += alphabet[genRnd(alphabet.size())];
    }

    return _result_pass;
}
 
void PassGenerator::init_alphabet()
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

    // return alphabet;
}
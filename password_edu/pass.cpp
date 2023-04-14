#include "gen.h"
#include "pass.h"

using namespace std;

Pass::Pass()
{
    // std::cout << "Hello! I will generate a password for you!\n";
    srand(time(NULL));
    init();
}

Pass::~Pass()
{
    // std::cout << "Password: Good bye!\n";
}

void Pass::test_fun_01()
{
    int counter = 2;
    do 
    {
        cout << counter << endl;
        counter += 2;
    } while (counter < 102);
}

int Pass::genRnd(int max)
{
    return rand() % max;
}

string Pass::run(int length)
{
    string res = "";
    for (int i = 0; i < length; ++i)
    {
        res += letters[genRnd(letters.size())];
    }
    return res;
}
 

vector<string> Pass::get_alphabet()
{
    return letters;
}

void Pass::init()
{
    letters.push_back("q");
    letters.push_back("w");
    letters.push_back("e");
    letters.push_back("r");
    letters.push_back("t");
    letters.push_back("y");
    letters.push_back("u");
    letters.push_back("i");
    letters.push_back("o");
    letters.push_back("p");
    letters.push_back("a");
    letters.push_back("s");
    letters.push_back("d");
    letters.push_back("f");
    letters.push_back("g");
    letters.push_back("h");
    letters.push_back("j");
    letters.push_back("k");
    letters.push_back("l");
    letters.push_back("z");
    letters.push_back("x");
    letters.push_back("c");
    letters.push_back("v");
    letters.push_back("b");
    letters.push_back("n");
    letters.push_back("m");
    letters.push_back("0");
    letters.push_back("1");
    letters.push_back("2");
    letters.push_back("3");
    letters.push_back("4");
    letters.push_back("5");
    letters.push_back("6");
    letters.push_back("7");
    letters.push_back("8");
    letters.push_back("9");    
    letters.push_back("Q");
    letters.push_back("W");
    letters.push_back("E");
    letters.push_back("R");
    letters.push_back("T");
    letters.push_back("Y");
    letters.push_back("U");
    letters.push_back("I");
    letters.push_back("O");
    letters.push_back("P");
    letters.push_back("A");
    letters.push_back("S");
    letters.push_back("D");
    letters.push_back("F");
    letters.push_back("G");
    letters.push_back("H");
    letters.push_back("J");
    letters.push_back("K");
    letters.push_back("L");
    letters.push_back("Z");
    letters.push_back("X");
    letters.push_back("C");
    letters.push_back("V");
    letters.push_back("B");
    letters.push_back("N");
    letters.push_back("M");
    letters.push_back("0");
}

void Pass::factorial()
{
    int factArg = 0;
    int i = 2;
    long int fact(1);

    do
    {
        cout << "Factorial of: ";
        cin >> factArg;

        if (factArg < 0)
        {
            cout << "No negative values, please" << endl;
        }   

    } while (factArg < 0);    
    
    while (i <= factArg)
    {
        fact = fact * i;
        cout << "npoM: " << fact << endl;
        i++;
    }
    
    cout << "The factorial of " << factArg << " is: " << fact << endl;

}


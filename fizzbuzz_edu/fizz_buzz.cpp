#include "fizz_buzz.h"

fizz_buzz::fizz_buzz()
{
    is_printed = false;
    nMaxVal = 0;
}

fizz_buzz::~fizz_buzz()
{

}

void fizz_buzz::Run()
{
    cout << "Enter max value: \n";
    cin >> nMaxVal;
    cout << "------------START-----------\n";
    // alg_one();
    alg_three();
}

void fizz_buzz::alg_one()
{
    for (int i = 1; i <= nMaxVal; i++)
    {
        bool byThree = (!(i % 3));
        bool byFive = (!(i % 5));

        if (byThree) std::cout << "Fizz";
        if (byFive) std::cout << "Buzz";
        if (!byThree && !byFive) std::cout << i;
        std::cout << std::endl;
    }
}

void fizz_buzz::alg_two()
{
   for (int i = 1; i <= nMaxVal; i++)
    {
        is_printed = false;
        //cout << "number: " << i << "(%3) = " << (i % 3) << "\n";
        //cout << "number: " << i << "(%5) = " << (i % 5) << "\n";
        // cout <<  div_three(i) << "\n\n";

        if (!div_three(i) && !div_five(i))
        {
            cout << ": " << i << " - FIZZ BUZZ" << "\n";
            is_printed = true;
        }
        if (!div_three(i) && (!is_printed))
        {
            cout << ": " << i << " - FIZZ" << "\n";
            is_printed = true;
        }
        if (!div_five(i) && (!is_printed))
        {
            cout << ": " << i << " - BUZZ" << "\n";
            is_printed = true;
        }
        if (!is_printed)
        {
            cout << ": " << i << "\n";
        }
    }
}

void fizz_buzz::alg_three()
{
    /*
     * Solve the task using 2 'if' statements
     */
    for (int i = 1; i <= nMaxVal; i++)
    {
        std::string sToPrint = std::to_string((_ULonglong)i);

        bool byThree = (!(i % 3));
        bool byFive = (!(i % 5));
        
        if (byThree) {std::cout << "Fizz"; sToPrint = ""; }
        if (byFive)  {std::cout << "Buzz"; sToPrint = ""; }
        
        // if (!byThree && !byFive) std::cout << i;
        
        std::cout << sToPrint << std::endl;
    }
}

bool fizz_buzz::div_three(int val)
{
    if (val % 3)
        return true;
    else
        return false;
}

bool fizz_buzz::div_five(int val)
{
    if (val % 5)
        return true;
    else
        return false;
}


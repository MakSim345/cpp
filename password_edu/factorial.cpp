#include "gen.h"
#include "factorial.h"

Factorial::Factorial()
{
    std::cout << "Hello! I will calculate a factorial for you!\n";
    srand(time(NULL));
}

Factorial::~Factorial()
{
    std::cout << "Factorial: Good bye!\n";
}

int Factorial::genRnd(int max)
{
    return rand() % max;
}

void Factorial::run()
{
    int factArg = 0;
    int i = 2;
    double long fact(1);

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


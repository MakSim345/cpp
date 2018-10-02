#include "utils.h"

int produceRND()
{
    static int nFirstTime = 1;
    int random;
 
    if (1 == nFirstTime)
    {
        srand (static_cast<unsigned int>(time (NULL)));
        nFirstTime = 0;
    }
    random = 1 + (rand() % 100);
    // random = 1 + (rand() % RND_MAX);
    return random;
}

void printRandomNumbers()
{
    int random_number = 0;
    CRandomNumbers *_myRND = new CRandomNumbers();
    for (int i = 0; i < 2000; i ++)
    {
        random_number = _myRND->getRandomNumber(0, 49);
        cout << i << " - Random number: " << random_number << endl;
    }
}
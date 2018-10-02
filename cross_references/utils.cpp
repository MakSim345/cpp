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
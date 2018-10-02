#include "timer.h"
#define RND_MAX 65536

int produceRND()
{
    static int nFirstTime = 1;
    int random_int;
 
    if (1 == nFirstTime)
    {
        srand (time (NULL));
        nFirstTime = 0;
    }
    random_int = 1 + (rand() % RND_MAX);

    return random_int;
}
 

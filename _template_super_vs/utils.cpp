#include "utils.h"

/*
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

*/

int produceRND()
{
    // Generate a random number between 0 and 100
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, 100);
    return dist(rng);
}

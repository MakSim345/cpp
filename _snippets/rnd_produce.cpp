#include <random>

// #define RND_MAX 65536
#define RND_MAX 1000000

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

int getRandomNumber()
{
    // Create a random device and use it to seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister engine

    std::uniform_int_distribution<> distr(1, 49);

    return distr(gen); // Generate and return the random number
}

#ifndef _RANDOM_GENERATOR_H_
#define _RANDOM_GENERATOR_H_

#include "gen.h"

// #define RND_MAX 10

class random_generator
{
public:

    // Constructor:
    random_generator()
    {
        // std::cout << "random_generator constructor called!" << std::endl;
        srand(time(NULL));
    }

    int get_tick()
    {
        // Create a random device and use it to seed the random number generator
        std::random_device rd;
        std::mt19937 gen(rd()); // Mersenne Twister engine

        // std::uniform_int_distribution<> distr(1, RAND_MAX);
        std::uniform_int_distribution<> distr(1, 10);

        return 1 + (distr(gen) % 10); // Generate and return the random number
    }

private:

};

#endif


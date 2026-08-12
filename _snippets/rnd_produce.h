#ifndef _RND_PRODUCE_
#define _RND_PRODUCE_
/*********************************************************************

  01.10.2004 Initial coding YS

**********************************************************************/
#include "gen.h"

int produceRND();

int getRandomNumber();

#endif



#ifdef TEXT_ONLY
A few clean ways:

1. Use type aliases

This keeps the declarations short and readable.

using Rng = std::mt19937;
using Dist = std::uniform_int_distribution<int>;

Rng rng(static_cast<unsigned int>(std::time(nullptr)));
Dist dist(0, 19);

2. Put setup into a helper method
Very clean at call site.

std::mt19937 make_rng()
{
    return std::mt19937(static_cast<unsigned int>(std::time(nullptr)));
}

then:

auto rng = make_rng();
std::uniform_int_distribution<int> dist(0, 19);

3. Use modern seeding (clean and better quality)

std::mt19937 make_rng()
{
    std::random_device rd;
    return std::mt19937(rd());
}

Then:

auto rng = make_rng();
std::uniform_int_distribution<int> dist(0, 19);

4. Also name your range constants
Improves readability immediately.

constexpr int kMin = 0;
constexpr int kMax = 19;
std::uniform_int_distribution<int> dist(kMin, kMax);

If you want shortest + cleanest in practice:
    - helper make_rng()
    - auto rng = make_rng();
    - named min/max constants for distribution.
#endif

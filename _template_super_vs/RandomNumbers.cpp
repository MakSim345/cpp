//============================================================
//
// Description:
// <purpose of this file>
//============================================================

#include "RandomNumbers.h"

int CRandomNumbers::getRandomNumber(int iMin, int iMax)
{
    static bool bIsInitialized = false;
    // int _tmp_rand_value = 0;
    int _retValue = 0;

    if ( !bIsInitialized )
    {
        initialize();
        bIsInitialized = true;
    }

    // Generate a random number between 0 and 100
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(iMin, iMax);
    _retValue = dist(rng);
    // _tmp_rand_value = rand();
    //_retValue = ( iMin + int( (iMax - iMin + 1) * _tmp_rand_value /(RND_MAX + 1.0) ) );
    return _retValue;
}

void CRandomNumbers::initialize()
{
    srand((unsigned)time(0));
    rand();
    return;
}

_ARRAY_INT CRandomNumbers::getRandomNumbers(int iMin, int iMax, int iSize, bool bUniqueOnlyFlag)
{
    _ARRAY_INT viRandomNumbers;
    map <int, int> viUniqueRandomNumbers;

    viRandomNumbers.clear();

    if ( !bUniqueOnlyFlag )
    {
        for ( int i = 0; i < iSize; i++ )
        {
            viRandomNumbers.push_back(getRandomNumber(iMin, iMax));
        }

        return viRandomNumbers;
    }


    for ( int i = 0; i < iSize; )
    {
        int iRandomNumber = getRandomNumber(iMin, iMax);

        if ( viUniqueRandomNumbers.find(iRandomNumber) == viUniqueRandomNumbers.end() )
        {
            viRandomNumbers.push_back(iRandomNumber);
            viUniqueRandomNumbers[iRandomNumber] = true;
            ++i;
        }
     }

    return viRandomNumbers;
}

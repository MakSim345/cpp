#include "winner.h"

Winner::Winner()
     :bWinnerM(false)
     ,strWinnerNameM("None")
     {};

bool Winner::checkWinner(int totalStepCtrP)
{
    if (true == bWinnerM)
    {
        std::cout << strWinnerNameM << " WIN by running " << totalStepCtrP << " steps!\n";
    }
    return bWinnerM;
}

void Winner::setWinner(std::string strWinnerP)
{
    if (bWinnerM)
        return;

    strWinnerNameM = strWinnerP;
    bWinnerM = true;
}
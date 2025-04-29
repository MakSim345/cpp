#ifndef _WUINNER_H_
#define _WUINNER_H_

#include "gen.h"

class Winner
{
public:

    Winner();
    ~Winner(){};
    bool checkWinner(int totalStepCtrP);
    void setWinner(std::string strWinnerP);
    std::string getWinnerName() { return strWinnerNameM; }

private:
    bool bWinnerM;
    std::string strWinnerNameM;
};

#endif

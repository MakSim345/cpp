#ifndef QUEENS_ORIG_H
#define QUEENS_ORIG_H

//============================================================
//
// Description:
//===========================================================

using namespace std;


class QueenOrig
{

public:
    QueenOrig();
   ~QueenOrig();
    void run();

private:
    int board[8][8];

    void resetQueen(int i, int j);
    void setQueen(int i, int j);
    bool tryQueen(int i);
    
};

#endif


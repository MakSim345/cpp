#ifndef QUEENS_LAB_H
#define QUEENS_LAB_H

//============================================================
//
// Description:
//===========================================================


class QueenLab
{

public:
    QueenLab();
   ~QueenLab();
    void run();
    void printBoard();

private:
    int board[8][8];

    void resetQueen(int i, int j);
    void setQueen(int i, int j);
    bool tryQueen(int i);
    
};

#endif


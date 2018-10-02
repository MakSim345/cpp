#include "gen.h"
#include "queens_lab.h"

QueenLab::QueenLab()
{
    for (int i=0; i<8; i++)
    {
      for (int j=0; j<8; j++)
      {
        board [i][j] = 0;
      }
    }
}

void QueenLab::printBoard()
{
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (board [i][j] == 1)
                std::cout << " x ";
            else
                std::cout << " . ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void QueenLab::setQueen(int i, int j)
{
  for (int x = 0; x < 8; x++)
    {
        ++ board[x][j];
        ++ board[i][x];
        int foo;
        foo = j - i + x;
        if (foo >= 0 && foo < 8)
        {
            ++ board[x][foo];
        }
        
        foo = j + i - x;
        if (foo >= 0 && foo < 8)
        {
            ++ board[x][foo];
        }       
    }
    board[i][j] = -1;
}

void QueenLab::resetQueen(int i, int j)
{
   for (int x=0; x<8; x++)
    {
        -- board[x][j];
        -- board[i][x];
        int foo;
        foo = j -i + x;
        if (foo >= 0 && foo < 8)
        {
            ++ board[x][foo];
        }
        foo = j +i - x;

        if (foo >= 0 && foo < 8)
        {
            ++ board[x][foo];
        }       
    }
    board[i][j] = -1;
}

bool QueenLab::tryQueen(int i)
{
    int _tmp = _getch();

    static int counter = 0;
    bool result = false; 
    printBoard();
    for (int j=0; j<8; j++)
    {   
        std::cout << "j = " << j << std::endl;
        std::cout << "i = " << i << std::endl;
        std::cout << "ctr = " << ++counter << std::endl;

        printBoard();

        if (board [i][j] == 0)
        {
            setQueen(i, j);
            if (i == 7)
            {
                result = true;
            }
            else
            {
                if (!(result == tryQueen(i+1)))
                    resetQueen(i, j);
            }
        }

        if (result)
        {
            break;
        }
    }
  return result;  
}

void QueenLab::run()
{
  this->tryQueen(0);
  this->printBoard();
}


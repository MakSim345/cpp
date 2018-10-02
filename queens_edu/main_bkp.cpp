#include <iostream>
#include "utils.h"

using namespace std;

inline float cube (const float s) {return s*s*s;}

int board[8][8];
void printBoard()
{
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (board [i][j] == 1)
                cout << " x ";
            else
                cout << " . ";
        }
        cout << endl;
    }
    cout << endl;
}

void setQueen(int i, int j)
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

void resetQueen(int i, int j)
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

// recoursive function:
bool tryQueen(int i)
{    
    static int counter = 0;
    bool result = false;    
    printBoard();
    for (int j=0; j<8; j++)
    {   
        cout << "j = " << j << endl;
        cout << "i = " << i << endl;
        cout << "ctr = " << ++counter << endl;

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

void initBoard ()
{
    for (int i=0; i<8; i++)
    {
      for (int j=0; j<8; j++)
      {
        board [i][j] = 0;
      }
    }
}

int main()
{
    initBoard ();
    tryQueen(0);
    printBoard();   
    


    /*
    cout << "Enter cube dimention: " ;
    float side;
    cin >> side;
    cout << "Cube with side " << side << " is equal to " << cube(side) << endl;
    */
    return 1;
}


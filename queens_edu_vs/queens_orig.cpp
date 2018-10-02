#include "gen.h"
#include "queens_orig.h"

QueenOrig::QueenOrig()
{

}

void QueenOrig::setQueen(int i, int j)
{
  for (int x = 0; x < 8; ++x)
  {
    ++board[x][j];
    ++board[i][x];
    int foo;
    foo = j - i + x;
    if (foo >= 0 && foo < 8)
      ++board[x][foo];
    foo = j + i - x;
    if (foo >= 0 && foo < 8)
      ++board[x][foo];
  }
  board[i][j] = -1;
}

void QueenOrig::resetQueen(int i, int j)
{
  for (int x = 0; x < 8; ++x)
  {
    --board[x][j];
    --board[i][x];
    int foo;
    foo = j - i + x;
    if (foo >= 0 && foo < 8)
      --board[x][foo];
    foo = j + i - x;
    if (foo >= 0 && foo < 8)
      --board[x][foo];
  }
  board[i][j] = 0;
}

bool QueenOrig::tryQueen(int i)
{
  bool result = false;
  for (int j = 0; j < 8; ++j)
  {
    if (board[i][j] == 0)
    {
      setQueen(i, j);
      if (i == 7)
	result = true;
      else
      {
	if (!(result = tryQueen(i + 1)))
	  resetQueen(i, j);
      }
    }
    if (result)
      break;
  }
  return result;
}

void QueenOrig::run()
{
for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j)
      board[i][j] = 0;
  tryQueen(0);
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      if (board[i][j] == -1)
	std::cout << "[]";
      else
	std::cout << ". ";
    }
    std::cout << std::endl;
  }
}


#include "gen.h" 
#include "utils.h"

std::string Timestamp()
{
    SYSTEMTIME xTime;
    ::GetSystemTime(&xTime);
    std::ostringstream xStream;
    xStream << xTime.wDay << "." 
            << xTime.wMonth << "."
            << xTime.wYear << " - "
            << xTime.wHour << "."
            << xTime.wMinute << "."
            << xTime.wSecond << "."
            << xTime.wMilliseconds;

    return xStream.str();
}

void shuffle (int **cardDeckDoubleArray)
{
    int row, column;
    int card_num;
    for (card_num = 1; card_num <=52; card_num++)
    {
        row=rand() % 4;
        column = rand() % 13;
        while (cardDeckDoubleArray[row][column] != 0)
        {
            row=rand() % 4;
            column = rand() % 13;
        }
        printf ("KapTa HoMep %d: arr[%d][%d]\n", card_num, row, column);
        cardDeckDoubleArray[row][column] = card_num;
    }
 
}

void deal(const int wDeck [][13], const char *wFace[], const char *wSuit[])
{
 return;
}

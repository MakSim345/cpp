#include "gen.h" 
#include "utils.h"

void shuffle (int **wDeck)
{
    int row, column;
    int card_num;
    for (card_num = 1; card_num <=52; card_num++)
    {
        row=rand() % 4;
        column = rand() % 13;
        while (wDeck[row][column] != 0)
        {
            row=rand() % 4;
            column = rand() % 13;
        }
        printf ("KapTa HoMep %d: wDeck[%d][%d]\n", card_num, row, column);
        wDeck[row][column] = card_num;
    }
 
}

void deal(const int wDeck [][13], const char *wFace[], const char *wSuit[])
{
 return;
}

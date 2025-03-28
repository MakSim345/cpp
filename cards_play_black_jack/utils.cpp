#include <stdio.h>
#include <string.h>
#include "gen.h"
#include "time.h"
#include<stdlib.h>
#include "utils.h"


void shuffle_cards()
{
    std::string suit[4] = {"4epBu", "6y6HbI", "TpeFbI", "nuku"};
    std::string face[13] = {"Ty3", "gBouka", "Tpouka", "4eTBepka",
                            "nqTepka", "wecTepka", "CeMepka", "BocMepka",
                            "geBqTka", "gecqTka", "BaLeT", "DaMa", "KopoLb"};
    int deck[4][13] = {0};
    int i=0;

    srand (time(NULL));
    // shuffle (deck);
}

/*
void shuffle (int wDeck [][13])
{
 	int row, column;
 	int card;
 	for (card = 1; card <=52; card++)
 	{
  		row=rand() % 4;
  		column = rand() % 13;
  		while (wDeck[row][column] != 0)
  		{
   			row=rand() % 4;
   			column = rand() % 13;
  		}
  		printf ("KapTa wDeck[%d][%d] 6ygeT %d\n", row, column, card );
  		wDeck[row][column] = card;
 	}

}
*/

void deal(const int wDeck [][13], const char *wFace[], const char *wSuit[])
{
 	return;
}


class Book
{
public:
    std::string TitleM;
    std::string AuthorM;
    int* RatesM;
    int RatesCounterM;

    Book(std::string TitleP, std::string AuthorP)
    {
        TitleM = TitleP;
        AuthorM = AuthorP;

        RatesCounterM = 2;
        RatesM = new int [RatesCounterM];

        std::cout << TitleM << " - Constructor invoked\n";
    }

   ~Book()
    {
        delete [] RatesM;
        std::cout << TitleM << " - Destructor invoked\n";
    }

};

void PrintIntroduction()
{
  int i;
  int nFrame = 59;
	printf ("\t%c", 201);
	for (i=0; i<nFrame; i++)
	   printf ("%c", 205);
  	printf ("%c\n", 187);
	printf ("\t%c Application printing out every 1 seconds the              %c\n", 186, 186);
	printf ("\t%c number of PPS signals in TestPPS value.                   %c\n", 186, 186);
	printf ("\t%c The TestPPS has to grow by 1 every second.                %c\n", 186, 186);
	printf ("\t%c Type 'Ctrl-X' for end.                                    %c\n", 186, 186);

	printf ("\t%c", 200);
	for (i=0; i<nFrame; i++)
	   printf ("%c", 205);
  printf ("%c\n", 188);
  //printf ("\n");


};


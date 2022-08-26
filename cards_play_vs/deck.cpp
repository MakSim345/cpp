#include "deck.h"

// Define counter in file scope.
int ElectricOven::gCounter = 0; 

// constructor
deck::deck()
    : m_cdeck('R')
    , m_nPosition(1)
    ,_my_oven(new ElectricOven())
    ,_oven(ElectricOven())
{
    //srand(time(NULL));
    // m_cdeck = 'R';
    // m_nPosition =1;
    
    // _my_oven = new ElectricOven();
    
    // std::cout << _my_oven->getColor();
    std::cout << "deck constructor start\n";
    _my_oven = new ElectricOven();
    // _oven = ElectricOven();
    
    std::cout << _my_oven->getColor() << "--\n";
    

    m_nWinner=0;
    m_random_value = 0;
    m_step = 0;
    mNumColumns = 13;
    mNumRows = 4;
    
    cardDeckArray.resize(mNumRows*mNumColumns, 0);
    std::cout << "deck constructor END\n";
}

void deck::set(int row, int col, int inT)
{
    cardDeckArray[row * mNumColumns + col] = inT;
}

int deck::get(size_t rowId, size_t colId)
{
    return cardDeckArray[rowId*mNumColumns + colId];
}

void deck::push_to_array()
{
    suit.push_back("4epBu");
    suit.push_back("6y6HbI");
    suit.push_back("TpeFbI");
    suit.push_back("nuku");
    
    face.push_back("Ty3");
    face.push_back("gBojka");
    face.push_back("Tpojka");
    face.push_back("4eTBepka");
    face.push_back("nqTepka");
    face.push_back("wecTepka"); 
    face.push_back("ceMepka");
    face.push_back("BocMepka");
    face.push_back("geBqTka");
    face.push_back("gecqTka");
    face.push_back("BaLeT");
    face.push_back("gaMa");
    face.push_back("KopoLb");
}

void deck::shuffle ()
{
    std::cout << "\nshuffle:" << _my_oven->getColor() << "\n";
    
    int row, column;
    int card_num;
    for (card_num = 1; card_num <=52; card_num++)
    {
        row=rand() % 4;
        column = rand() % 13;
        
        std::cout << "shuffle:" << row << ", " << column << "\n";
        while (get(row, column) != 0)
        {
            row=rand() % 4;
            column = rand() % 13;
        }
        
        // printf ("KapTa HoMep %d: cardDeckArray[%s][%s]\n", card_num, suit[row], face[column]);
        std::cout << "KapTa HoMep " << card_num << ": [" << suit[row] << "]-[" << face[column] << "]\n";
        set(row, column, card_num);
        
        // cardDeckArray[row][column] = card_num;
    }
    std::cout << "\nshuffle end\n";
}

void deck::print_deck()
{
    int card_num;
    std::cout << "-------Function print_deck------------\n";
    
    for (card_num = 1; card_num <=52; card_num++)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (card_num == get(i, j))
                std::cout << "KapTa HoMep " << card_num << ": [" << suit[i] << "]-[" << face[j] << "]\n";

            }
        }
    }
}

int deck::run ()
{
    //srand(time(NULL));
    return 1+rand()%10;
}

deck::~deck()
{

}

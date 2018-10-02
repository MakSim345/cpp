#ifndef _DECK_H_
#define _DECK_H_

#include "gen.h"
#include "ElectricOven.h"

// class ElectricOven;

std::string Timestamp();

class deck
{
public: 
 
    deck();
    ~deck();

    int run(); 
    void shuffle ();
    void set(int row, int col, int inT);
    int get(size_t rowId, size_t colId);
    void push_to_array();
    void print_deck();

private:
    char m_cRabbit;
    int m_nPosition;
    int m_nWinner;   
    int m_random_value;
    int m_step;

    char m_cdeck;
    int mNumColumns;
    int mNumRows;    
    ElectricOven _oven;
    ElectricOven* _my_oven;
    // std::vector < std::vector <int> > cardDeckArray;
    std::vector <int> cardDeckArray;
    
    std::vector <std::string> suit;
    std::vector <std::string> face;                      
};


/*
template <class T>
class matrix2D 
{ 
    std::vector<T> data;
    int columns;
public:
    T &operator()(int x, int y) 
    {
        return y * columns + x;
    }

    matrix2D(int x, int y) : data(x*y), columns(x) {}
};
*/


#endif

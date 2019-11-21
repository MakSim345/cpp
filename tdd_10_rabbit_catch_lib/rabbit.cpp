#include "rabbit.h"

//Rabbit functions:

Rabbit::Rabbit(Winner *_win)
    :m_strName("Rabbit")
    ,m_cRabbit('R')
    ,m_nPosition(1)
    ,m_step(0)
{
    winner = _win;
}

void Rabbit::move(int _new_rnd_value)
{
    int m_random_value = _new_rnd_value; // Random_R();

    switch (m_random_value)
    {
    case 1: case 2:
        setPos(0); // sleep
        break;
    case 3: case 4:
        setPos(9); // long jump
        break;
    case 5: case 6: case 7:
        setPos(1); // short jump
        break;
    case 8:
        setPos(-12); // long slippery
        break;
    case 9: case 10:
        setPos(-2); // short slippery
        break;
    default:
        break;
    }

}

int Rabbit::Random_R ()
{
    return 1+rand()%10;
}

void Rabbit::setPos (int nPos)
{
    m_step = nPos;
    //std::cout<<"Rabbit pos going to: " << nPos << std::endl;

    m_nPosition=m_nPosition + nPos;

    if (m_nPosition <= 0)
    {
        m_nPosition = 1;
        //std::cout<<"Rabbit pos = 1. Reason: " << m_nPosition << std::endl;
    }

    if (m_nPosition >= MAIN_LINE)
    {
        m_nPosition = MAIN_LINE;
        // std::string rbt("Rabbit");
        this->winner->setWinner(m_strName);
    }

    //std::cout<<"Rabbit new pos: " << m_nPosition << std::endl;
}

Rabbit::~Rabbit()
{

}

//--------
//SuperRabbit functions:

SuperRabbit::SuperRabbit(std::string _myName, Winner *_win)
    :Animal( _myName, _win)
{

}

int SuperRabbit::move(int _new_rnd_value)
{
    int m_random_value = _new_rnd_value; // Random_R();

    switch (m_random_value)
    {
    case 1: case 2:
        setPos(0); // sleep
        break;
    case 3: case 4:
        setPos(9); // long jump
        break;
    case 5: case 6: case 7:
        setPos(1); // short jump
        break;
    case 8:
        setPos(-12); // long slippery
        break;
    case 9: case 10:
        setPos(-2); // short slippery
        break;
    default:
        break;
    }
    return pos();
}

SuperRabbit::~SuperRabbit()
{

}

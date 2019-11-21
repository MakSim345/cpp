#include "turtle.h"

//--------
//SuperRabbit functions:

SuperTurtle::SuperTurtle(std::string _myName, Winner *_win)
    :Animal( _myName, _win)
{

}

int SuperTurtle::move(int _new_rnd_value)
{
    int m_random_value = _new_rnd_value; // Random_R();

    switch (m_random_value)
    {
     case 1: case 2: case 3: case 4: case 5:
        setPos(3); // quick moving
        break;
     case 6: case 7:
        setPos(-6); // slippery
        break;
    case 8: case 9: case 10:
        setPos(1); // moving
        break;
    default:
        break;
    }

    return pos();
}

SuperTurtle::~SuperTurtle()
{

}


//Turtle functions:

Turtle::Turtle(Winner *_win)
    :m_strName("Turtle")
    ,m_cTurtle('T')
    ,m_nPosition(1)
    ,m_step (0)
{
    winner = _win;
}

void Turtle::setPos (int nPos)
{
    m_step = nPos;
    m_nPosition=m_nPosition + nPos;

    if (m_nPosition <= 0)
    {
        m_nPosition=1;
    }
    if (m_nPosition >= MAIN_LINE)
    {
        m_nPosition = MAIN_LINE;
        winner->setWinner(m_strName);
        //cout<<"turtle WON ( function message)" << endl;
    }
}

void Turtle::move(int _new_rnd_value)
{
    int m_random_value = _new_rnd_value; // Random_R();

    switch (m_random_value)
    {
     case 1: case 2: case 3: case 4: case 5:
        setPos(3); // quick moving
        break;
     case 6: case 7:
        setPos(-6); // slippery
        break;
    case 8: case 9: case 10:
        setPos(1); // moving
        break;
    default:
        break;
    }

}

Turtle::~Turtle ()
{

}

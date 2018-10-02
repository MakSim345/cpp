#include "winner.h"

Winner::Winner()
     :m_bWinner(false)
     ,strWinnerName("None")
     {};

bool Winner::win(int stepCounter) 
{
    if (true==m_bWinner)
    {        
        std::cout << strWinnerName << " WIN by running " << stepCounter << " steps!\n";
    }
    return m_bWinner;
}

void Winner::setWinner(std::string _strWinner)
{
    strWinnerName = _strWinner;
    m_bWinner = true;
}


//Animal functions:

Animal::Animal(std::string _myName, Winner *_win)
{
    m_MyChar = _myName.at(0);//'R';
    m_strName = _myName;
    m_nPosition =1;
    m_step = 0;
    winner = _win;
}

void Animal::setPos(int nPos)
{
    m_step = nPos;
    //std::cout<<"Animal pos going to: " << nPos << std::endl;
 
    m_nPosition=m_nPosition + nPos;

    if (m_nPosition <= 0)
    {
        m_nPosition = 1;
        //std::cout<<"Animal pos = 1. Reason: " << m_nPosition << std::endl;
    }

    if (m_nPosition >= MAIN_LINE)
    {
        m_nPosition = MAIN_LINE;        
        this->winner->setWinner(m_strName);
    }

    //std::cout<<"Animal new pos: " << m_nPosition << std::endl;
}

Animal::~Animal()
{

}

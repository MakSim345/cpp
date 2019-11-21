#ifndef _WUINNER_H_
#define _WUINNER_H_

#include "gen.h"

class Winner
{
public:

    Winner();
    ~Winner(){};
    bool win(int stepCounter);
    void setWinner(std::string _strWinner);
    std::string getWinnerName() { return strWinnerName; }

private:
    bool m_bWinner;
    std::string strWinnerName;

};


class Animal
{
public:

    Animal(std::string _myName, Winner *_win);
    virtual ~Animal();

    char getChar() {return m_MyChar;}
    int pos() {return m_nPosition;}
    int getSteps() {return m_step;}
    void setPos(int nPos);
    virtual int move(int _new_rnd_value) = 0;

private:
    char m_MyChar;
    int m_nPosition;
    int m_step;
    std::string m_strName;
    Winner *winner;
};


#endif

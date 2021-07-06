#ifndef _TURTLE_H_
#define _TURTLE_H_

#include "gen.h"
#include "winner.h"

class SuperTurtle : public Animal
{
public:
    SuperTurtle(std::string _myName, Winner *_win);
   ~SuperTurtle();
    int move(int _new_rnd_value);

private:

};

class Turtle
{
public:
    Turtle(Winner *_win);
    ~Turtle();

    char getChar() {return m_cTurtle;}
    int pos() {return m_nPosition;}
    int getSteps() {return m_step;}

    void setPos(int nPos);     
    void move(int _new_rnd_value);
    

private:
    char m_cTurtle;
    std::string m_strName;
    int m_nPosition;
    int m_step;
    Winner *winner;
};

#endif

#ifndef _RABBIT_H_
#define _RABBIT_H_

#include "gen.h"
#include "winner.h"

class SuperRabbit : public Animal
{
public:
    SuperRabbit(std::string _myName, Winner *_win);
   ~SuperRabbit();
    int move(int _new_rnd_value); 
    
private:
    
};


class Rabbit
{
public:
 
    Rabbit(Winner *_win);
    ~Rabbit();

    char getChar() {return m_cRabbit;}
    int pos() {return m_nPosition;}
    int getSteps() {return m_step;}
    void setPos(int nPos);  
    void move(int _new_rnd_value); 

private:
    char m_cRabbit;
    int m_nPosition;
    int Random_R ();//function
    int m_step;
    std::string m_strName;
    Winner *winner;
};

#endif

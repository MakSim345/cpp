#include "gen.h"
#include "rabbit.h"
#include "turtle.h"
#include "winner.h"
#include "random_generator.h"

void mySleep(int sleepMs)
{
#ifdef LINUX
    usleep(sleepMs * 1000);   // usleep takes sleep time in us
#endif

#ifdef WINDOWS
    Sleep(sleepMs);
#endif
}

int main()
{   
    bool RValue = false;
    int _rabbit_cur_pos = 0;
    int _turtle_cur_pos = 0;
    int stepCounter = 0;
    int m_step = 0;

    Winner *winner = new Winner();
    // Rabbit *rabbit = new Rabbit(winner);
    // Turtle *turtle = new Turtle(winner);
    SuperRabbit *rabbit = new SuperRabbit("Rabbit", winner);
    SuperTurtle *turtle = new SuperTurtle("Turtle", winner);
    
    random_generator *rg = new random_generator();    

    // srand(time(NULL));
    
    std::cout << "GONG! And they are go!!!\n";
    
    do
    {
        stepCounter++;
        _rabbit_cur_pos = rabbit->move(rg->get_tick());
        _turtle_cur_pos = turtle->move(rg->get_tick());
        
        /*
        m_step = rabbit->Get_Step();        
        std::cout  << " Rabbit got " << m_step  << " steps" << "\n";
        
        m_step = turtle->Get_Step();
        std::cout  << " Turtle got " << m_step  << " steps" << "\n";
               
         _rabbit_cur_pos = rabbit->pos();
        std::cout  << stepCounter << " - Rabbit on position " << _rabbit_cur_pos << "\n";

         _turtle_cur_pos = turtle->pos();
        std::cout  << stepCounter << " - Turtle on position " << _turtle_cur_pos << "\n";
        */

        for (int i = 0; i <= MAIN_LINE; ++i)
        {
            if (_turtle_cur_pos == i)
            {
                if (_turtle_cur_pos == _rabbit_cur_pos)
                {
                    std::cout << "X";
                }
                else
                {
                    std::cout << turtle->getChar();   
                }
            }
            else if (_rabbit_cur_pos == i)
            {
                std::cout << rabbit->getChar();
            }
            else
            {
                std::cout << "_";
            }
        }

        std::cout << "\n\n";

        mySleep(40);

        if (true == winner->win(stepCounter))
        {            
            RValue = true;
            // std::cout << "Rabbit WIN by running " << stepCounter << " steps!\n";
        } 
        /*
        if (rabbit->Get_Winner())
        {            
            RValue = true;
            std::cout << "Rabbit WIN by running " << stepCounter << " steps!\n";
        }

        if (turtle->Get_Winner())
        {            
            RValue = true;
            std::cout << "Turtle WIN by running " << stepCounter << " steps!\n";
        }
        */

    } while (!RValue);
    
    // printf("This is output from my first program!\n");
    return 0;
}


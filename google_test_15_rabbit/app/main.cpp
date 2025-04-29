#include "gen.h"
#include "rabbit.h"
#include "turtle.h"
#include "winner.h"
#include "random_generator.h"

void mySleep(int sleepMs)
{
#ifdef _WIN32
    Sleep(sleepMs);
#else
    usleep(sleepMs * 1000);   // usleep takes sleep time in us
#endif
}

int main()
{
    bool RValue = false;
    int rabbitCurPos = 0;
    int turtleCurPos = 0;
    int stepCounter = 0;
    int m_step = 0;

    // random_generator *rg = new random_generator();
    random_generator rg;

    Winner winner;

    SuperRabbit *rabbit = new SuperRabbit("Rabbit", &winner);
    SuperTurtle *turtle = new SuperTurtle("Turtle", &winner);


    std::cout << "GONG! And they are go!!!\n";

    do
    {
        stepCounter++;
        rabbitCurPos = rabbit->move(rg.get_tick());
        turtleCurPos = turtle->move(rg.get_tick());

        /*
        m_step = rabbit->Get_Step();
        std::cout  << " Rabbit got " << m_step  << " steps" << "\n";

        m_step = turtle->Get_Step();
        std::cout  << " Turtle got " << m_step  << " steps" << "\n";

         _rabbit_cur_pos = rabbit->getPosition();
        std::cout  << stepCounter << " - Rabbit on position " << _rabbit_cur_pos << "\n";

         _turtle_cur_pos = turtle->getPosition();
        std::cout  << stepCounter << " - Turtle on position " << _turtle_cur_pos << "\n";
        */

        for (int i = 0; i <= MAIN_LINE; ++i)
        {
            if (turtleCurPos == i)
            {
                if (turtleCurPos == rabbitCurPos)
                {
                    std::cout << "X";
                }
                else
                {
                    std::cout << turtle->getChar();
                }
            }
            else if (rabbitCurPos == i)
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

        if (true == winner.checkWinner(stepCounter))
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

    return 0;
}


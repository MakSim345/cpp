// MyTestSuite1.h
#include <cxxtest/TestSuite.h>

#include "gen.h"
#include "winner.h"
#include "rabbit.h"
#include "turtle.h"
#include "random_generator.h"

class MyTestSuite: public CxxTest::TestSuite
{
public:
    void testAddition(void)
    {
        std::cout << "\ntestAddition";
        TS_ASSERT (1 + 1 > 1);
        TS_ASSERT_EQUALS (1 + 1, 2);
    }

    void testMultiplication(void)
    {
        std::cout << "\ntestMultiplication";
        TS_ASSERT_EQUALS(2 * 2, 4)
    }

    void test_a_winner()
    {
        std::cout << "\ntest_a_winner";
        Winner tw = Winner();
        TS_ASSERT_EQUALS(tw.win(1), false);
    }

    void test_rabbit_pos()
    {
        std::cout << "\ntest_rabbit_pos";
        Winner *tw = new Winner();
        Rabbit *rabbit = new Rabbit(tw);
        int pos_to_test = 4;
        int pos_neg = -10;
        int pos_over = MAIN_LINE + 1;
        rabbit->setPos(pos_to_test);
        TS_ASSERT_EQUALS(rabbit->pos(), pos_to_test + 1);

        rabbit->setPos(0); // set to zero for clearance
        rabbit->setPos(pos_neg);
        TS_ASSERT_EQUALS(rabbit->pos(), 1);

        rabbit->setPos(0); // set to zero for clearance
        rabbit->setPos(pos_over);
        TS_ASSERT_EQUALS(rabbit->pos(), MAIN_LINE);
    }

    void test_super_rabbit_pos()
    {
        std::cout << "\ntest_super_rabbit_pos";
        Winner *tw = new Winner();
        SuperRabbit *rabbit = new SuperRabbit("Rabbit", tw);
        int pos_to_test = 4;
        int pos_neg = -10;
        int pos_over = MAIN_LINE + 1;
        rabbit->setPos(pos_to_test);
        TS_ASSERT_EQUALS(rabbit->pos(), pos_to_test + 1);

        rabbit->setPos(0); // set to zero for clearance
        rabbit->setPos(pos_neg);
        TS_ASSERT_EQUALS(rabbit->pos(), 1);

        rabbit->setPos(0); // set to zero for clearance
        rabbit->setPos(pos_over);
        TS_ASSERT_EQUALS(rabbit->pos(), MAIN_LINE);
    }

    void test_super_turtle_pos()
    {
        std::cout << "\ntest_super_turtle_pos";
        Winner *tw = new Winner();
        SuperTurtle * trt = new SuperTurtle("Turtle", tw);
        int pos_to_test = 4;
        int pos_neg = -10;
        int pos_over = MAIN_LINE + 1;
        trt->setPos(pos_to_test);
        TS_ASSERT_EQUALS(trt->pos(), pos_to_test + 1);

        trt->setPos(0); // set to zero for clearance
        trt->setPos(pos_neg);
        TS_ASSERT_EQUALS(trt->pos(), 1);

        trt->setPos(0); // set to zero for clearance
        trt->setPos(pos_over);
        TS_ASSERT_EQUALS(trt->pos(), MAIN_LINE);
    }

};

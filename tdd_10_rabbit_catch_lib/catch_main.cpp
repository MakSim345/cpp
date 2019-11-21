#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
// #include <cxxtest/catch.hpp>

#include "gen.h"
#include "winner.h"
#include "rabbit.h"
#include "turtle.h"
#include "random_generator.h"

void SetConsoleColour(WORD* Attributes, DWORD Colour)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Colour);
}

void ResetConsoleColour(WORD Attributes)
{
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

class Test_RND_Generator
{
public:
   random_generator *rg;

   Test_RND_Generator()
    {
        setUp();
    }

    void setUp()
    {
       rg = new random_generator();
    }

    int get_tick()
    {
        return rg->get_tick();
    }
};


class Test_Rabbit
{
public:
    Winner *winner;
    Rabbit *rabbit;

    Test_Rabbit()
    {
        setUp();
    }

    void setUp()
    {
        winner = new Winner();
        rabbit = new Rabbit(winner);
    }

    // void tearDown();

    Rabbit* get_r()
    {
        return rabbit;
    }

};

TEST_CASE( "Testing RND", "[test RND]" )
{
    std::cout << "Testing RND - [...]\n";
    Test_RND_Generator tg = Test_RND_Generator();
    // REQUIRE(tg.get_tick() == 4);
}

TEST_CASE( "Testing a rabbit", "[Constructor]" )
{
    Test_Rabbit tr = Test_Rabbit();
    REQUIRE(tr.get_r()->getChar() == 'R' );
    REQUIRE(tr.get_r()->pos() == 1 );
    std::cout << "Testing a rabbit - [Constructor]\n";
    // REQUIRE(tr.get_r()->Get_Winner() == 0 );
    // REQUIRE(tr.get_r()->Get_Step() == 0 );
}

TEST_CASE( "Testing a winner", "[Constructor]" )
{
    WORD Attributes = 0;

    // yellow FOREGROUND_RED | FOREGROUND_GREEN );
    // Cyan FOREGROUND_BLUE | FOREGROUND_GREEN
    // SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
    // SetConsoleColour(&Attributes,  FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

    std::cout << "Testing a winner - [Constructor]\n";
    Winner tw = Winner();
    std::cout << "Testing a winner - [winner == FALSE]\n";
    REQUIRE(tw.win(1) == false);
    std::cout << "Testing a winner - [Name == None]\n";
    REQUIRE(tw.getWinnerName() == "None");
    ResetConsoleColour(Attributes);
}

TEST_CASE( "Testing real winner", "[Check winner]" )
{
    WORD Attributes = 0;

    // yellow FOREGROUND_RED | FOREGROUND_GREEN );
    // Cyan FOREGROUND_BLUE | FOREGROUND_GREEN
    // SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
    // SetConsoleColour(&Attributes,  FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

    std::cout << "Testing real winner!\n";
    Winner tw = Winner();
    tw.setWinner("Rabbit");
    REQUIRE(tw.win(1) == true);
    REQUIRE(tw.getWinnerName() == "Rabbit");

    tw.setWinner("Turtle");
    REQUIRE(tw.win(1) == true);
    REQUIRE(tw.getWinnerName() == "Rabbit");
    std::cout << "Testing a winner - [Rabbit]\n";

    ResetConsoleColour(Attributes);
}


/*
TEST_CASE( "Testing a rabbit position", "[Set Position]" )
{
    Winner *tw = new Winner();
    Rabbit *rabbit = new Rabbit(tw);
    int pos_to_test = 4;
    int pos_neg = -10;
    int pos_over = MAIN_LINE + 1;
    rabbit->Set_Position(pos_to_test);
    REQUIRE(rabbit->pos() == pos_to_test + 1 );

    rabbit->Set_Position(0); // set to zero for clearance
    rabbit->Set_Position(pos_neg);
    REQUIRE(rabbit->pos() == 1 );

    rabbit->Set_Position(0); // set to zero for clearance
    rabbit->Set_Position(pos_over);
    REQUIRE(rabbit->pos() == MAIN_LINE );
}
*/

/*
TEST_CASE( "Factorials are computed", "[factorial]" )
{
    REQUIRE( Factorial(0) == 1 );
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
    REQUIRE( Factorial(11) == 3628801 );
}
*/

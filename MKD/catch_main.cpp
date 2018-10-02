#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
// #include "catch.hpp"
#include <cxxtest/catch.hpp>
// #include "patient.h"

/*
unsigned int Factorial(unsigned int number) 
{
    return number <= 1 ? number : Factorial(number-1)*number;
}
*/

unsigned int Factorial(unsigned int number) 
{
  return number > 1 ? Factorial(number-1)*number : 1;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) 
{
    REQUIRE( Factorial(0) == 1 );
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}



/*
TEST_CASE( "Test constructor", "[patient]" )
{
    //std::cout << "..test name John\n";   
    REQUIRE(_my_patient->getName() == "John");
    CHECK(_my_patient->getName() == "John");
    //std::cout << "..test bed25\n";
    REQUIRE(_my_patient->getLocation() == "bed25");
    
    _my_patient->terminate(true);
    REQUIRE_FALSE(_my_patient->isAlive() );
}
*/


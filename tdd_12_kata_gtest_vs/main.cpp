// main.cpp : Defines the entry point for the console application.
//
// #include "stdafx.h"
#include "gen.h"

struct BankAccount 
{
    int ballance;

    BankAccount()
    {
    }

    explicit BankAccount(const int pBalance) 
        : ballance (pBalance)
    {
    }

};


int add (std::string numbers)
{
    if (numbers.empty())
    {
        return 0;
    }

    int result;
    int _tellg;
    std::stringstream ss(numbers);
    ss >> result;
    std::cout << "result: " << result << "\n";
    // std::cout << "ss.tellg()    : " << ss.tellg() << "\n";
    std::cout << "numbers.size(): " << numbers.size() << "\n";    
    _tellg = ss.tellg();
    while (_tellg != numbers.size())
    {
        char delim;
        int next;
        ss >> delim;
        ss >> next;
        result += next;
        _tellg = ss.tellg();
    }   

    return result;
}

// An empty string returns zero:
TEST(add_emptyString, returns0)
{
    int result = add("");
    EXPECT_EQ(result, 0);
}
// A single number returns the value:
TEST(add_oneNumberString, returns1)
{
    int result = add("1");
    EXPECT_EQ(result, 1);
}
// Two numbers, comma delimited, returns the sum:
TEST(add_twoNumberString, returns3)
{
    int result = add("1,2");
    EXPECT_EQ(result, 3);
}
// Three numbers, delimited either way, returns the sum:
TEST(add_threeNumberString, returns3)
{
    int result = add("1,1,1");
    EXPECT_EQ(result, 3);
}
TEST(add_fiveNumberString, returns5)
{
    int result = add("1,1,1,1,1");
    EXPECT_EQ(result, 5);
}

/*
TEST(AccountTest, BancAccountStartsEmpty)
{
    BankAccount account;
    EXPECT_EQ(0, account.ballance);
}
*/

/*
TEST(blahTest, blah1) 
{
    EXPECT_EQ(1, 1);
}

*/
int main(int argc, char** argv)
{
    int returnValue = 0;
    testing::InitGoogleTest(&argc, argv);
    returnValue = RUN_ALL_TESTS();
    printf ("Application complete.\n");
    system ("PAUSE");
    return returnValue;
}
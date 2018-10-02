#include <cxxtest/TestSuite.h>
#include "calc.h"
/*
 * 
The String Calculator Kata

Like the Bowling Kata, this kata, made popular by Roy Osherove, comes with a precise set of steps to follow. The essence is a method that given a delimited string, returns the sum of the values. I’ve always preferred my kata to define the tests I will follow every time through the exercise, so here are the tests I use for this one:

Source: http://en.wikipedia.org/wiki/File:Timex_T5E901_Ironman_Triathlon_30_Lap_FLIX.jpg

   1. An empty string returns zero
   2. A single number returns the value
   3. Two numbers, comma delimited, returns the sum
   4. Two numbers, newline delimited, returns the sum
   5. Three numbers, delimited either way, returns the sum
   6. Negative numbers throw an exception
   7. Numbers greater than 1000 are ignored
   8. A single char delimiter can be defined on the first line (e.g. //# for a ‘#’ as the delimiter)
   9. A multi char delimiter can be defined on the first line (e.g. //[###] for ‘###’ as the delimiter)
   10. Many single or multi-char delimiters can be defined (each wrapped in square brackets)

I rarely bother with Test #10 when I do it, because it feels like a big step to take all at once, but Roy does include it in his definition, and I have it in my kata notebook.
 */


class CalcTestSuite : public CxxTest::TestSuite
{
public:
    // An empty string returns zero:
    void test_add_emptyString_returns0()
    {
        int result = add("");
        TS_ASSERT_EQUALS(result, 0);
    }
    // A single number returns the value:
    void test_add_oneNumberString_returns1()
    {
        int result = add("1");
        TS_ASSERT_EQUALS(result, 1);
    }
    // Two numbers, comma delimited, returns the sum:
    void test_add_twoNumberString_returns2()
    {
        int result = add("1,2");
        TS_ASSERT_EQUALS(result, 3);
    }
    // Three numbers, delimited either way, returns the sum:
    void test_add_threeNumberString_returns3()
    {
        int result = add("1,1,1");
        TS_ASSERT_EQUALS(result, 3);
    }
    void test_add_fiveNumberString_returns5()
    {
        int result = add("1,1,1,1,1");
        TS_ASSERT_EQUALS(result, 5);
    }
    // Two numbers, newline delimited, returns the sum
    void test_add_newLineDelimTwoNumberString_returns2()
    {
        int result = add("1\n1");
        TS_ASSERT_EQUALS(result, 2);
    }
};


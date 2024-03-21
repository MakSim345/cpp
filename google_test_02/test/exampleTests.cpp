#include  "../example.h"
#include <gtest/gtest.h>

bool bFoo()
{
    return false;
}

int add(int valueOneP, int valueTwoP)
{
    return (valueOneP + valueTwoP);
}

TEST(ExampleTests, firstSimpleTest)
{
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(ExampleTests, TestIsTrueFalse)
{
    EXPECT_EQ(true, true);
    const bool result= bFoo();
    EXPECT_EQ(true, result);
}

TEST(ExampleTests, IsOneZero)
{
    ASSERT_EQ(1, 1) << "TEST IsOneZero: 1 is not equal 0";
    // ASSERT_EQ(1, 0) << "TEST IsOneZero: 1 is not equal 0";
}

TEST(ExampleTests, SQUARE)
{
  int x = 5;
  int expectedSquare = 25;
  EXPECT_EQ(expectedSquare, Square(x));
}


TEST(ExampleTests, MAC)
{
  int x = 42;
  int y = 16;
  int sum = 100;
  int oldSum = sum;
  int expectedNewSum = oldSum + x * y;

  EXPECT_EQ(expectedNewSum, sum);

  EXPECT_EQ(expectedNewSum, MAC(x, y, sum));

  EXPECT_EQ(expectedNewSum, sum);
}

TEST(ExampleTests, PositiveNos)
{
    EXPECT_EQ(16, add(8, 8));
}

int main(int argc, char** argv)
{
    int returnValue = 0;
    ::testing::InitGoogleTest(&argc, argv);
    returnValue = RUN_ALL_TESTS();

    printf("Application complete.\n");
    // system("PAUSE");

    return returnValue;
 }


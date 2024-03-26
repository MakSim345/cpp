#include "gen.h"
#include <gtest/gtest.h>

class MyClass
{
public:
    MyClass (int bvP) : baseValueM (bvP)
    {}

    void Increment (int byValueP)
    {
        baseValueM += byValueP;
    }

    int getValue () {return baseValueM;}

private:
    int baseValueM;
};


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

TEST(ExampleTests, IsOneZero)
{
    ASSERT_EQ(1, 1) << "TEST IsOneZero: 1 is not equal 0";
    // ASSERT_EQ(1, 0) << "TEST IsOneZero: 1 is not equal 0";
}

TEST(ExampleTests, PositiveNos)
{
    EXPECT_EQ(16, add(8, 8));
}


struct MyTestSuite : public testing::Test
{
    MyClass *uutMyClass;
    void SetUp()
    {
        // std::cout << "--->C-Tor\na;
        uutMyClass = new MyClass(100);
    }

    void TearDown()
    {
        // std::cout << "--->D-Tor\n";
        delete uutMyClass;
    }
};

TEST_F(MyTestSuite, testAddition)
{
    ASSERT_EQ (100 + 5, 105);
}

TEST_F(MyTestSuite, testComparison)
{
    // TS_ASSERT_LESS_THAN
    ASSERT_LT((int)1, (unsigned long)2);
    ASSERT_LT(-3, -2);
}

TEST_F(MyTestSuite, testEquality)
{
    // TS_ASSERT_EQUALS( 1, 2 );
    ASSERT_EQ( 'a', 'a' );
    ASSERT_NE( 'a', 'A' );
    // ASSERT_EQ( 1.0, -12345678900000000000000000000000000000000000000000.1234 );
    ASSERT_NE( 1.0, -12345678900000000000000000000000000000000000000000.1234 );
}


TEST_F(MyTestSuite, testMultiplication)
{
    ASSERT_EQ (10 * 10, 100) << "TEST Multiplication: not equal 100";
    ASSERT_EQ (2 * 2, 4);
    ASSERT_EQ (4 * 4, 16);
    // ASSERT_EQ (2 * 2, 3); // -2 * -2 = 4?
}

TEST_F(MyTestSuite, inc_by_10)
{
    uutMyClass->Increment(10);
    //Assert
    ASSERT_EQ (uutMyClass->getValue(), 110);
}

/*

class MyTestSuite: public CxxTest::TestSuite
{
public:
    void testAddition(void)
    {
        TS_ASSERT (1 + 1 > 1);
        TS_ASSERT_EQUALS (1 + 1, 2);
    }

    void testMultiplication(void)
    {
        TS_ASSERT_EQUALS(2 * 2, 4)
    }

    void TestMultiplication()
    {
        TS_ASSERT_EQUALS(2 * 2, 4);
        TS_ASSERT_EQUALS(4 * 4, 16);
        TS_ASSERT_DIFFERS(2 * 2, 3); // -2 * -2 = 4?
    }

    void testComparison()
    {
        TS_ASSERT_LESS_THAN((int)1, (unsigned long)2);
        TS_ASSERT_LESS_THAN(-3, -2);
    }

    void testEquality()
    {
        //TS_ASSERT_EQUALS( 1, 1 );
        TS_ASSERT_EQUALS( 1, 2 );
        //TS_ASSERT_EQUALS( 'a', 'A' );
        // TS_ASSERT_EQUALS( 1.0, -12345678900000000000000000000000000000000000000000.1234 );
    }
};
*/


int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

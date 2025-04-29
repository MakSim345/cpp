#include <gtest/gtest.h>
#include "../random_generator.h"
#include "../winner.h"
#include "../rabbit.h"
#include "../turtle.h"

// Test for random_generator
TEST(RandomGeneratorTest, GetTickInRange)
{
    random_generator gen;

    for (int i = 0; i < 100; ++i)
    {
        int tick = gen.get_tick();
        // printf("%d, ", tick);
        EXPECT_GE(tick, 1); // Check that tick is >= 1
        EXPECT_LE(tick, 10); // Check that tick is <= 10
    }
}

// Test the default state of Winner
TEST(WinnerTest, DefaultState)
{
    Winner winner;

    // Initially, there should be no winner
    EXPECT_FALSE(winner.checkWinner(0));
    EXPECT_EQ(winner.getWinnerName(), "None");
}

// Test setting and getting the winner's name
TEST(WinnerTest, SetAndGetWinnerName)
{
    Winner winner;

    // Set a winner's name
    winner.setWinner("Rabbit");

    // Verify the winner's name
    EXPECT_EQ(winner.getWinnerName(), "Rabbit");
}

// Test the checkWinner method
TEST(WinnerTest, CheckWinner)
 {
    Winner winner;
    const int steps = 189;
    // Simulate a scenario where the winner is determined
    EXPECT_FALSE(winner.checkWinner(50)); // No winner at step 50

    winner.setWinner("Turtle");
    EXPECT_TRUE(winner.checkWinner(steps)); // Winner at some step
}

TEST(SimpleTest, Addition)
{
    EXPECT_EQ(2 + 2, 4);
}

// Main function for running all tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

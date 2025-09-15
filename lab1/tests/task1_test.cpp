#include <gtest/gtest.h>

#include <task1/counter.h>

TEST(CounterTests, CountOnesInNumberTests) {
    ASSERT_EQ(CountOnesInNumber(0b0), 0);
    ASSERT_EQ(CountOnesInNumber(0b1), 1);
    ASSERT_EQ(CountOnesInNumber(0b101011), 4);
    ASSERT_EQ(CountOnesInNumber(0b111111), 6);
}

TEST(CounterTests, CountOnesInSequenceTests) {
    ASSERT_EQ(CountOnesInSequence(0, 0), 0);
    ASSERT_EQ(CountOnesInSequence(0, 1), 1);
    ASSERT_EQ(CountOnesInSequence(2, 7), 11);
}

int main(int argc,
         char **argv) {
    ::testing::InitGoogleTest(&argc,
                              argv);

    return RUN_ALL_TESTS();
}

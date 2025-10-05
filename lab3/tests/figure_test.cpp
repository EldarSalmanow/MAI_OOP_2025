#include <gtest/gtest.h>

#include <lab3/figure.h>


TEST(FigureTests, FigureTest) {
    ASSERT_EQ(1, 1);
}

int main(int argc,
         char **argv) {
    ::testing::InitGoogleTest(&argc,
                              argv);

    return RUN_ALL_TESTS();
}

#include <gtest/gtest.h>

#include <stdexcept>

#include <lab2/money.h>

TEST(MoneyTests, DefaultConstructor) {
    Money money;

    EXPECT_NO_THROW(money.Eq(Money("0.00")));
}

TEST(MoneyTests, SizeConstructor) {
    Money money1(1, 5); // 0.05
    Money money2(2, 3); // 0.33
    Money money3(3, 1); // 1.11

    EXPECT_TRUE(money1.Eq(Money("0.05")));
    EXPECT_TRUE(money2.Eq(Money("0.33")));
    EXPECT_TRUE(money3.Eq(Money("1.11")));
}

TEST(MoneyTests, InitializerListConstructor) {
    Money money1{1};       // 0.01
    Money money2{0, 1};    // 0.10
    Money money3{0, 0, 1}; // 1.00
    Money money4{4, 3, 2, 1}; // 12.34

    EXPECT_TRUE(money1.Eq(Money("0.01")));
    EXPECT_TRUE(money2.Eq(Money("0.10")));
    EXPECT_TRUE(money3.Eq(Money("1.00")));
    EXPECT_TRUE(money4.Eq(Money("12.34")));
}

TEST(MoneyTests, StringConstructor) {
    Money money1("0.01"); // 0.01
    Money money2("0.10"); // 0.1
    Money money3("1.00"); // 1.00
    Money money4("12.34"); // 12.34

    EXPECT_TRUE(money1.Eq(Money({1})));
    EXPECT_TRUE(money2.Eq(Money({0, 1})));
    EXPECT_TRUE(money3.Eq(Money({0, 0, 1})));
    EXPECT_TRUE(money4.Eq(Money({4, 3, 2, 1})));

    EXPECT_THROW(Money("12.a34"), std::invalid_argument);
    EXPECT_THROW(Money("12.3"), std::invalid_argument);
    EXPECT_THROW(Money("12.345"), std::invalid_argument);
}

TEST(MoneyTests, CopyConstructor) {
    Money original{4, 3, 2, 1}; // 12.34
    Money copy(original);
    EXPECT_TRUE(copy.Eq(original));
}

TEST(MoneyTests, MoveConstructor) {
    Money original{4, 3, 2, 1}; // 12.34
    Money moved(std::move(original));
    EXPECT_TRUE(moved.Eq(Money("12.34")));
}

TEST(MoneyTests, AddDifferentSizes) {
    Money m1{1};        // 0.01
    Money m2{0, 0, 1};  // 1.00
    Money result = m1.Add(m2);
    Money expected{1, 0, 1}; // 1.01
    EXPECT_TRUE(result.Eq(expected));
}

TEST(MoneyTests, AddSingleDigit) {
    Money m1{5}; // 0.05
    Money m2{3}; // 0.03
    Money result = m1.Add(m2);
    Money expected{8}; // 0.08
    EXPECT_TRUE(result.Eq(expected));
}

TEST(MoneyTests, AddTwoDigits) {
    Money m1{5, 1}; // 0.15
    Money m2{3, 2}; // 0.23
    Money result = m1.Add(m2);
    Money expected{8, 3}; // 0.38
    EXPECT_TRUE(result.Eq(expected));
}

TEST(MoneyTests, AddWithCarryToNewDigit) {
    Money m1{9, 9};    // 0.99
    Money m2{1};        // 0.01
    Money result = m1.Add(m2);
    Money expected{0, 0, 1}; // 1.00
    EXPECT_TRUE(result.Eq(expected));
}

TEST(MoneyTests, SubDifferentSizes) {
    Money m1{1, 0, 1}; // 1.01
    Money m2{1};        // 0.01
    Money result = m1.Sub(m2);
    Money expected{0, 0, 1}; // 1.00
    EXPECT_TRUE(result.Eq(expected));
}

TEST(MoneyTests, SubSingleDigit) {
    Money m1{8}; // 0.08
    Money m2{3}; // 0.03
    Money result = m1.Sub(m2);
    Money expected{5}; // 0.05
    EXPECT_TRUE(result.Eq(expected));
}

TEST(MoneyTests, SubWithBorrow) {
    Money m1{0, 0, 1}; // 1.00
    Money m2{1};        // 0.01
    Money result = m1.Sub(m2);
    Money expected{9, 9}; // 0.99
    EXPECT_TRUE(result.Eq(expected));
}

TEST(MoneyTests, SubNegativeResult) {
    Money m1{1}; // 0.01
    Money m2{2}; // 0.02
    EXPECT_THROW(m1.Sub(m2), std::invalid_argument);
}

TEST(MoneyTests, LessThanDifferentSizes) {
    Money m1{1};       // 0.01
    Money m2{0, 0, 1}; // 1.00
    EXPECT_TRUE(m1.Less(m2));
    EXPECT_FALSE(m2.Less(m1));

    Money m3{9, 9};    // 0.99
    Money m4{0, 0, 1}; // 1.00
    EXPECT_TRUE(m3.Less(m4));
    EXPECT_FALSE(m4.Less(m3));
}

TEST(MoneyTests, GreaterThanDifferentSizes) {
    Money m1{0, 0, 1}; // 1.00
    Money m2{1};        // 0.01
    EXPECT_TRUE(m1.Greater(m2));
    EXPECT_FALSE(m2.Greater(m1));
}

TEST(MoneyTests, EqualDifferentSizes) {
    Money m1{0, 0, 0, 1}; // 10.00
    Money m2{0, 0, 0, 1}; // 10.00
    Money m3{0, 0, 1};    // 1.00

    EXPECT_TRUE(m1.Eq(m1));
    EXPECT_TRUE(m1.Eq(m2));
    EXPECT_FALSE(m1.Eq(m3));
}

TEST(MoneyTests, EqualSameValueDifferentSizes) {
    Money m1{0, 0, 0};     // 0.00
    Money m2{0};           // 0.00
    Money m3{0, 0};        // 0.00

    EXPECT_TRUE(m1.Eq(m2));
    EXPECT_TRUE(m1.Eq(m3));
    EXPECT_TRUE(m2.Eq(m3));
}

TEST(MoneyTests, SingleDigitZero) {
    Money zero{0};
    Money one{1};

    EXPECT_TRUE(zero.Eq(Money("0.00")));
    EXPECT_TRUE(one.Eq(Money("0.01")));

    Money result1 = zero.Add(one);
    EXPECT_TRUE(result1.Eq(one));

    Money result2 = one.Sub(one);
    EXPECT_TRUE(result2.Eq(zero));
}

TEST(MoneyTests, TwoDigits) {
    Money m1{5, 1}; // 0.15
    Money m2{3, 2}; // 0.23

    EXPECT_TRUE(m1.Less(m2));
    EXPECT_TRUE(m2.Greater(m1));

    Money result = m1.Add(m2);
    EXPECT_TRUE(result.Eq(Money("0.38")));
}

TEST(MoneyTests, KopeckOverflowSingleDigit) {
    Money m1{9}; // 0.09
    Money m2{2}; // 0.02
    Money result = m1.Add(m2);
    Money expected{1, 1}; // 0.11
    EXPECT_TRUE(result.Eq(expected));
}

TEST(MoneyTests, KopeckOverflowTwoDigits) {
    Money m1{9, 9}; // 0.99
    Money m2{1};     // 0.01
    Money result = m1.Add(m2);
    Money expected{0, 0, 1}; // 1.00
    EXPECT_TRUE(result.Eq(expected));
}

TEST(MoneyTests, ComplexOperationsMixedSizes) {
    Money m1{4, 3, 2, 1}; // 12.34
    Money m2{6, 5};        // 0.56

    Money addResult = m1.Add(m2);
    Money expectedAdd{0, 9, 2, 1}; // 12.90
    EXPECT_TRUE(addResult.Eq(expectedAdd));

    Money subResult = m1.Sub(m2);
    Money expectedSub{8, 7, 1, 1}; // 11.78
    EXPECT_TRUE(subResult.Eq(expectedSub));
}

TEST(MoneyTests, VeryLargeDifferenceInSizes) {
    Money m1{0, 0, 0, 0, 0, 0, 0, 0, 1}; // 100000000.00
    Money m2{1};                          // 0.01

    Money result = m1.Add(m2);
    Money expected{1, 0, 0, 0, 0, 0, 0, 0, 1}; // 100000000.01
    EXPECT_TRUE(result.Eq(expected));

    EXPECT_TRUE(m1.Greater(m2));
    EXPECT_TRUE(m2.Less(m1));
}

TEST(MoneyTests, ImmutabilityAfterOperations) {
    Money original{1, 2, 3}; // 3.21
    Money operand{4, 5};     // 0.54

    Money addResult = original.Add(operand);
    Money subResult = original.Sub(operand);

    Money expectedOriginal{1, 2, 3};
    EXPECT_TRUE(original.Eq(expectedOriginal));
    Money expectedOperand{4, 5};
    EXPECT_TRUE(operand.Eq(expectedOperand));
}

TEST(MoneyTests, CloneWithDifferentSizes) {
    Money original1{1};           // 0.01
    Money original2{4, 3, 2, 1};  // 12.34

    Money clone1 = original1.Clone();
    Money clone2 = original2.Clone();

    EXPECT_TRUE(original1.Eq(clone1));
    EXPECT_TRUE(original2.Eq(clone2));
}

TEST(MoneyTests, ZeroRepresentations) {
    Money zero1{0};
    Money zero2{0, 0};
    Money zero3{0, 0, 0};
    Money zero4{0, 0, 0, 0};

    EXPECT_TRUE(zero1.Eq(zero2));
    EXPECT_TRUE(zero1.Eq(zero3));
    EXPECT_TRUE(zero1.Eq(zero4));
    EXPECT_TRUE(zero2.Eq(zero3));
    EXPECT_TRUE(zero3.Eq(zero4));

    Money one{1};
    Money result1 = zero1.Add(one);
    EXPECT_TRUE(result1.Eq(one));

    Money result2 = one.Sub(one);
    EXPECT_TRUE(result2.Eq(zero1));
}

TEST(MoneyTests, AddEqWithDifferentSizes) {
    Money m1{1, 2, 3}; // 3.21
    Money m2{4, 5};     // 0.54
    Money result = m1.AddEq(m2);
    Money expected{5, 7, 3}; // 3.75
    EXPECT_TRUE(result.Eq(expected));
    EXPECT_TRUE(m1.Eq(Money({1, 2, 3})));
}

TEST(MoneyTests, SubEqWithDifferentSizes) {
    Money m1{5, 7, 3}; // 3.75
    Money m2{4, 5};     // 0.54
    Money result = m1.SubEq(m2);
    Money expected{1, 2, 3}; // 3.21
    EXPECT_TRUE(result.Eq(expected));
    EXPECT_TRUE(m1.Eq(Money({5, 7, 3})));
}

int main(int argc,
         char **argv) {
    ::testing::InitGoogleTest(&argc,
                              argv);

    return RUN_ALL_TESTS();
}

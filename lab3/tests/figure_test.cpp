#include <gtest/gtest.h>

#include <sstream>

#include <lab3/rhomb.h>
#include <lab3/pentagon.h>
#include <lab3/hexagon.h>

static const char* rhomb_input = R"(
0 0  1 0  1 1  0 1
)"; // 4 points

static const char* pentagon_input = R"(
0 0  1 0  1.5 1  0.5 1.7  -0.5 1
)"; // 5 points

static const char* hexagon_input = R"(
0 0  1 0  2 1  1.5 2  0.5 2  -0.5 1
)"; // 6 points

TEST(PointTest, EqualityAndIostreamFormat) {
    Point a{1.0, 2.0};
    Point b{1.0, 2.0};
    Point c{2.0, 3.0};

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a == c);

    {
        std::stringstream in("1 2");
        Point parsed;
        in >> parsed;
        EXPECT_TRUE(parsed == a);
    }

    {
        std::stringstream out;
        out << a;
        std::string s = out.str();
        EXPECT_NE(s.find('['), std::string::npos);
        EXPECT_NE(s.find(';'), std::string::npos);
        EXPECT_NE(s.find(']'), std::string::npos);

        std::ostringstream expected;
        expected << "[" << a.X() << "; " << a.Y() << "]";
        EXPECT_EQ(s, expected.str());
    }
}

TEST(RhombTest, ReadFromNumericInputAndCopyMoveEquality) {
    std::stringstream ss(rhomb_input);
    Rhomb r;
    ss >> r;

    Rhomb r_copy(r);
    EXPECT_TRUE(r == r_copy);

    Rhomb r_assigned;
    r_assigned = r;
    EXPECT_TRUE(r_assigned == r);

    Rhomb r_moved(std::move(r_copy));
    EXPECT_TRUE(r_moved == r);

    Rhomb r_move_assigned;
    r_move_assigned = std::move(r_assigned);
    EXPECT_TRUE(r_move_assigned == r);
}

TEST(RhombTest, OutputFormatContainsPointBracketsAndSemicolons) {
    std::stringstream in(rhomb_input);
    Rhomb r;
    in >> r;

    std::stringstream out;
    out << r;
    std::string s = out.str();

    EXPECT_NE(s.find('['), std::string::npos);
    EXPECT_NE(s.find(';'), std::string::npos);
    EXPECT_NE(s.find(']'), std::string::npos);
}

TEST(RhombTest, DoubleAndCenterConsistency) {
    std::stringstream in(rhomb_input);
    Rhomb r;
    in >> r;

    double d1 = static_cast<double>(r);
    Rhomb r_copy(r);
    double d2 = static_cast<double>(r_copy);
    EXPECT_DOUBLE_EQ(d1, d2);

    Point center1 = r.CenterOfRotation();
    Point center2 = r_copy.CenterOfRotation();
    EXPECT_TRUE(center1 == center2);
}

TEST(PentagonTest, ReadFromNumericInputAndCopyMoveEquality) {
    std::stringstream ss(pentagon_input);
    Pentagon p;
    ss >> p;

    Pentagon p_copy(p);
    EXPECT_TRUE(p == p_copy);

    Pentagon p_moved(std::move(p_copy));
    EXPECT_TRUE(p_moved == p);

    Pentagon p_assign;
    p_assign = p;
    EXPECT_TRUE(p_assign == p);
}

TEST(PentagonTest, OutputFormatCheckAndDouble) {
    std::stringstream in(pentagon_input);
    Pentagon p;
    in >> p;

    std::stringstream out;
    out << p;
    std::string s = out.str();
    EXPECT_NE(s.find('['), std::string::npos);
    EXPECT_NE(s.find(';'), std::string::npos);

    double d1 = static_cast<double>(p);
    double d2 = static_cast<double>(p);
    EXPECT_DOUBLE_EQ(d1, d2);
}

TEST(HexagonTest, ReadFromNumericInputAndCopyMoveEquality) {
    std::stringstream ss(hexagon_input);
    Hexagon h;
    ss >> h;

    Hexagon h_copy(h);
    EXPECT_TRUE(h == h_copy);

    Hexagon h_moved(std::move(h_copy));
    EXPECT_TRUE(h_moved == h);

    Hexagon h_assign;
    h_assign = h;
    EXPECT_TRUE(h_assign == h);
}

TEST(HexagonTest, OutputFormatAndCenter) {
    std::stringstream in(hexagon_input);
    Hexagon h;
    in >> h;

    std::stringstream out;
    out << h;
    std::string s = out.str();
    EXPECT_NE(s.find('['), std::string::npos);
    EXPECT_NE(s.find(';'), std::string::npos);

    Point c1 = h.CenterOfRotation();
    Hexagon copy(h);
    Point c2 = copy.CenterOfRotation();
    EXPECT_TRUE(c1 == c2);
}

TEST(PolymorphismTest, BaseReferenceOutputHasPointFormattingAndInputViaBaseReadsNumeric) {
    std::stringstream in(rhomb_input);
    Rhomb r;
    in >> r;

    std::stringstream out;
    const Figure &figRef = r;
    out << figRef;
    std::string s = out.str();
    EXPECT_NE(s.find('['), std::string::npos);
    EXPECT_NE(s.find(';'), std::string::npos);

    Rhomb other;
    std::stringstream in2(rhomb_input);
    Figure &figRefOther = other;
    in2 >> figRefOther;
    Figure *figPointer = &other;
    in2 >> *figPointer;
    EXPECT_TRUE(other == r);
}

TEST(PointTest, ZeroAndNegativeValues) {
    Point a{0.0, -0.0};
    Point b{-0.0, 0.0};
    EXPECT_TRUE(a == b);

    Point c{1e-9, -1e-9};
    EXPECT_FALSE(c == a);
}

int main(int argc,
         char **argv) {
    ::testing::InitGoogleTest(&argc,
                              argv);

    return RUN_ALL_TESTS();
}

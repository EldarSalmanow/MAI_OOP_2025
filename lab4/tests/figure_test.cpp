#include <gtest/gtest.h>
#include <sstream>

#include <lab4/trapezoid.h>
#include <lab4/rectangle.h>
#include <lab4/square.h>

static const char *trapezoid_input = R"(
0 0  2 0  1.5 1  0.5 1
)"; // 4 points

static const char *rectangle_input = R"(
0 0  2 0  2 1  0 1
)"; // 4 points

static const char *square_input = R"(
0 0  1 0  1 1  0 1
)"; // 4 points

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
        Point<double> parsed{};
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

TEST(TrapezoidTest, ReadFromNumericInputAndCopyMoveEquality) {
    std::stringstream ss(trapezoid_input);
    Trapezoid<double> t;
    ss >> t;

    Trapezoid t_copy(t);
    EXPECT_TRUE(t == t_copy);

    Trapezoid<double> t_assigned;
    t_assigned = t;
    EXPECT_TRUE(t_assigned == t);

    Trapezoid t_moved(std::move(t_copy));
    EXPECT_TRUE(t_moved == t);

    Trapezoid<double> t_move_assigned;
    t_move_assigned = std::move(t_assigned);
    EXPECT_TRUE(t_move_assigned == t);
}

TEST(TrapezoidTest, OutputFormatContainsPointBracketsAndSemicolons) {
    std::stringstream in(trapezoid_input);
    Trapezoid<double> t;
    in >> t;

    std::stringstream out;
    out << t;
    std::string s = out.str();

    EXPECT_NE(s.find('['), std::string::npos);
    EXPECT_NE(s.find(';'), std::string::npos);
    EXPECT_NE(s.find(']'), std::string::npos);
}

TEST(TrapezoidTest, DoubleAndCenterConsistency) {
    std::stringstream in(trapezoid_input);
    Trapezoid<double> t;
    in >> t;

    double d1 = static_cast<double>(t);
    Trapezoid t_copy(t);
    double d2 = static_cast<double>(t_copy);
    EXPECT_DOUBLE_EQ(d1, d2);

    Point center1 = t.CenterOfRotation();
    Point center2 = t_copy.CenterOfRotation();
    EXPECT_TRUE(center1 == center2);
}

TEST(TrapezoidTest, AreaCalculation) {
    std::stringstream in(trapezoid_input);
    Trapezoid<double> t;
    in >> t;

    double area = static_cast<double>(t);
    // Для трапеции с основаниями 2 и 1, высотой 1: площадь = (2 + 1) * 1 / 2 = 1.5
    EXPECT_NEAR(area, 1.5, 1e-9);
}

TEST(TrapezoidTest, CenterOfRotation) {
    std::stringstream in(trapezoid_input);
    Trapezoid<double> t;
    in >> t;

    Point center = t.CenterOfRotation();
    // Центр описанной окружности вокруг трапеции
    // Для равнобедренной трапеции центр должен быть на середине между основаниями
    Point expected_center{1.0, 0.5};
    EXPECT_TRUE(center == expected_center);
}

TEST(RectangleTest, ReadFromNumericInputAndCopyMoveEquality) {
    std::stringstream ss(rectangle_input);
    Rectangle<double> r;
    ss >> r;

    Rectangle r_copy(r);
    EXPECT_TRUE(r == r_copy);

    Rectangle r_moved(std::move(r_copy));
    EXPECT_TRUE(r_moved == r);

    Rectangle<double> r_assign;
    r_assign = r;
    EXPECT_TRUE(r_assign == r);
}

TEST(RectangleTest, OutputFormatCheckAndDouble) {
    std::stringstream in(rectangle_input);
    Rectangle<double> r;
    in >> r;

    std::stringstream out;
    out << r;
    std::string s = out.str();
    EXPECT_NE(s.find('['), std::string::npos);
    EXPECT_NE(s.find(';'), std::string::npos);

    double d1 = static_cast<double>(r);
    double d2 = static_cast<double>(r);
    EXPECT_DOUBLE_EQ(d1, d2);
}

TEST(RectangleTest, AreaCalculation) {
    std::stringstream in(rectangle_input);
    Rectangle<double> r;
    in >> r;

    double area = static_cast<double>(r);
    // Для прямоугольника 2x1: площадь = 2 * 1 = 2
    EXPECT_NEAR(area, 2.0, 1e-9);
}

TEST(RectangleTest, CenterOfRotation) {
    std::stringstream in(rectangle_input);
    Rectangle<double> r;
    in >> r;

    Point center = r.CenterOfRotation();
    // Центр прямоугольника - пересечение диагоналей
    Point expected_center{1.0, 0.5};
    EXPECT_TRUE(center == expected_center);
}

TEST(SquareTest, ReadFromNumericInputAndCopyMoveEquality) {
    std::stringstream ss(square_input);
    Square<double> s;
    ss >> s;

    Square s_copy(s);
    EXPECT_TRUE(s == s_copy);

    Square s_moved(std::move(s_copy));
    EXPECT_TRUE(s_moved == s);

    Square<double> s_assign;
    s_assign = s;
    EXPECT_TRUE(s_assign == s);
}

TEST(SquareTest, OutputFormatAndCenter) {
    std::stringstream in(square_input);
    Square<double> s;
    in >> s;

    std::stringstream out;
    out << s;
    std::string s_str = out.str();
    EXPECT_NE(s_str.find('['), std::string::npos);
    EXPECT_NE(s_str.find(';'), std::string::npos);

    Point c1 = s.CenterOfRotation();
    Square copy(s);
    Point c2 = copy.CenterOfRotation();
    EXPECT_TRUE(c1 == c2);
}

TEST(SquareTest, AreaCalculation) {
    std::stringstream in(square_input);
    Square<double> s;
    in >> s;

    double area = static_cast<double>(s);
    // Для квадрата 1x1: площадь = 1 * 1 = 1
    EXPECT_NEAR(area, 1.0, 1e-9);
}

TEST(SquareTest, CenterOfRotationForRotationalSymmetry) {
    std::stringstream in(square_input);
    Square<double> s;
    in >> s;

    Point center = s.CenterOfRotation();
    // Центр квадрата (точка пересечения диагоналей) - центр вращательной симметрии
    Point expected_center{0.5, 0.5};
    EXPECT_TRUE(center == expected_center);
}

TEST(PolymorphismTest, BaseReferenceOutputHasPointFormattingAndInputViaBaseReadsNumeric) {
    std::stringstream in(square_input);
    Square<double> s;
    in >> s;

    std::stringstream out;
    const Figure<double> &figRef = s;
    out << figRef;
    std::string s_str = out.str();
    EXPECT_NE(s_str.find('['), std::string::npos);
    EXPECT_NE(s_str.find(';'), std::string::npos);

    Square<double> other;
    std::stringstream in2(square_input);
    Figure<double> &figRefOther = other;
    in2 >> figRefOther;
    Figure<double> *figPointer = &other;
    in2 >> *figPointer;
    EXPECT_TRUE(other == s);
}


TEST(PolymorphismTest, AreaCalculationThroughBaseReference) {
    std::stringstream in(square_input);
    Square<double> s;
    in >> s;

    const Figure<double> &figRef = s;
    double area = static_cast<double>(figRef);
    EXPECT_NEAR(area, 1.0, 1e-9);
}

TEST(PolymorphismTest, CenterOfRotationThroughBaseReference) {
    std::stringstream in(rectangle_input);
    Rectangle<double> r;
    in >> r;

    const Figure<double> &figRef = r;
    Point center = figRef.CenterOfRotation();
    Point expected_center{1.0, 0.5};
    EXPECT_TRUE(center == expected_center);
}

TEST(PointTest, ZeroAndNegativeValues) {
    Point a{0.0, -0.0};
    Point b{-0.0, 0.0};
    EXPECT_TRUE(a == b);

    Point c{1e-9, -1e-9};
    EXPECT_FALSE(c == a);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

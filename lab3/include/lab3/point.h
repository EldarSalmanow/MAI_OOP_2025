#ifndef MAI_OOP_2025_POINT_H
#define MAI_OOP_2025_POINT_H

#include <iostream>


class Point {
public:

    Point();

    Point(double x,
          double y);

    Point(const Point &point);

    Point(Point &&point) noexcept;

public:

    double X() const;

    double Y() const;

public:

    bool operator==(const Point &point) const;

    bool operator!=(const Point &point) const;

    Point &operator=(const Point &point);

    Point &operator=(Point &&point) noexcept;

public:

    friend std::istream &operator>>(std::istream &istream, Point &point);

    friend std::ostream &operator<<(std::ostream &ostream, const Point &point);

private:

    double _x, _y;
};

std::istream &operator>>(std::istream &istream, Point &point);

std::ostream &operator<<(std::ostream &ostream, const Point &point);

#endif //MAI_OOP_2025_POINT_H

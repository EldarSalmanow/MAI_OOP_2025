#include <lab3/point.h>

#define EPSILON 1e-9


Point::Point() = default;

Point::Point(double x,
             double y)
        : _x(x),
          _y(y) {}

Point::Point(const Point &point) = default;

Point::Point(Point &&point) noexcept = default;

double Point::X() const {
    return _x;
}

double Point::Y() const {
    return _y;
}

bool Point::operator==(const Point &point) const {
    return (std::abs(_x - point._x) < EPSILON)
        && (std::abs(_y - point._y) < EPSILON);
}

bool Point::operator!=(const Point &point) const {
    return !(*this == point);
}

Point &Point::operator=(const Point &point) = default;

Point &Point::operator=(Point &&point) noexcept = default;

std::istream &operator>>(std::istream &istream, Point &point) {
    istream >> point._x >> point._y;

    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const Point &point) {
    ostream << "[" << point._x << "; " << point._y << "]";

    return ostream;
}

#ifndef MAI_OOP_2025_POINT_H
#define MAI_OOP_2025_POINT_H

#include <iostream>


const double EPSILON = 1e-9;

template<typename T>
concept IsScalar = std::is_scalar_v<T>;

template<typename T>
struct EqHelper;

template<IsScalar T>
class Point {
public:

    Point() = default;

    Point(T x,
          T y)
            : _x(x),
              _y(y) {}

    Point(const Point &point) = default;

    Point(Point &&point) noexcept = default;

public:

    T X() const {
        return _x;
    }

    T Y() const {
        return _y;
    }

public:

    bool operator==(const Point &point) const {
        return (std::abs(_x - point._x) < EPSILON)
            && (std::abs(_y - point._y) < EPSILON);
    }

    bool operator!=(const Point &point) const {
        return !(*this == point);
    }

    Point &operator=(const Point &point) = default;

    Point &operator=(Point &&point) noexcept = default;

public:

    template<typename U>
    friend std::istream &operator>>(std::istream &istream, Point<U> &point);

    template<typename U>
    friend std::ostream &operator<<(std::ostream &ostream, const Point<U> &point);

private:

    T _x, _y;
};

template<typename T>
std::istream &operator>>(std::istream &istream, Point<T> &point) {
    istream >> point._x >> point._y;

    return istream;
}

template<typename T>
std::ostream &operator<<(std::ostream &ostream, const Point<T> &point) {
    ostream << "[" << point._x << "; " << point._y << "]";

    return ostream;
}

#endif //MAI_OOP_2025_POINT_H

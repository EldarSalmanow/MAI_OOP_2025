#include <cmath>

#include <lab7/point.h>


Point::Point(std::uint64_t x,
             std::uint64_t y)
        : _x(x),
          _y(y) {}

double Point::DistanceTo(const Point &point) const {
    auto x_distance = static_cast<double>(_x) - static_cast<double>(point._x);
    auto y_distance = static_cast<double>(_y) - static_cast<double>(point._y);

    return std::sqrt(x_distance * x_distance + y_distance * y_distance);
}

auto Point::GetX() const -> std::uint64_t {
    return _x;
}

auto Point::GetY() const -> std::uint64_t {
    return _y;
}

auto Point::SetX(std::uint64_t x) -> void {
    _x = x;
}

auto Point::SetY(std::uint64_t y) -> void {
    _y = y;
}

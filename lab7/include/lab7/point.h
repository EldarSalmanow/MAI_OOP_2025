#ifndef MAI_OOP_2025_POINT_H
#define MAI_OOP_2025_POINT_H

#include <cstdint>


class Point {
public:

    Point(std::uint64_t x,
          std::uint64_t y);

public:

    double DistanceTo(const Point &point) const;

public:

    auto GetX() const -> std::uint64_t;

    auto GetY() const -> std::uint64_t;

    auto SetX(std::uint64_t x) -> void;

    auto SetY(std::uint64_t y) -> void;

private:

    std::uint64_t _x, _y;
};

#endif //MAI_OOP_2025_POINT_H
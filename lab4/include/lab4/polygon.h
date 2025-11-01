#ifndef MAI_OOP_2025_POLYGON_H
#define MAI_OOP_2025_POLYGON_H

#include <cstdint>
#include <vector>

#include <lab4/figure.h>


template<typename T>
class Polygon : public Figure<T> {
public:

    explicit Polygon(std::uint64_t points_count)
            : _points(),
              _points_count(points_count) {
        _points.resize(_points_count);
    }

    Polygon(const Polygon<T> &polygon)
            : _points(polygon._points),
              _points_count(polygon._points_count) {}

    Polygon(Polygon &&polygon) noexcept
            : _points(std::move(polygon._points)),
              _points_count(polygon._points_count) {}

public:

    Point<T> CenterOfRotation() const override {
        T x_average = {}, y_average = {};

        for (std::uint64_t i = 0; i < _points_count; ++i) {
            x_average += _points[i].X();
            y_average += _points[i].Y();
        }

        return {
                x_average / static_cast<T>(_points_count),
                y_average / static_cast<T>(_points_count)
        };
    }

    std::istream &Input(std::istream &istream) override {
        for (std::uint64_t i = 0; i < _points_count; ++i) {
            istream >> _points[i];
        }

        return istream;
    }

    std::ostream &Output(std::ostream &ostream) const override {
        for (std::uint64_t i = 0; i < _points_count - 1; ++i) {
            ostream << _points[i] << " ";
        }

        ostream << _points[_points_count - 1] << std::endl;

        return ostream;
    }

public:

    Polygon &operator=(const Polygon &polygon) {
        if (this == &polygon) {
            return *this;
        }

        if (_points_count != polygon._points_count) {
            throw std::runtime_error("Polygons with different points count!");
        }

        _points = polygon._points;

        return *this;
    }

    Polygon &operator=(Polygon &&polygon) noexcept {
        if (this == &polygon) {
            return *this;
        }

        _points = std::move(polygon._points);

        return *this;
    }

    bool operator==(const Polygon &polygon) const {
        if (_points.size() != polygon._points.size()) {
            return false;
        }

        for (std::uint64_t i = 0; i < _points.size(); ++i) {
            if (_points[i] != polygon._points[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Polygon &polygon) const {
        return !(*this == polygon);
    }

public:

    operator T() const override {
        T x_y_sum = {}, y_x_sum = {};

        for (uint64_t i = 0; i < _points_count - 1; ++i) {
            x_y_sum += _points[i].X() * _points[i + 1].Y();
            y_x_sum += _points[i].Y() * _points[i + 1].X();
        }

        x_y_sum += _points[_points_count - 1].X() * _points[0].Y(); // x_n * y_1
        y_x_sum += _points[_points_count - 1].Y() * _points[0].X(); // y_n * x_1

        return std::abs(x_y_sum - y_x_sum) / T {2};
    }

protected:

    std::vector<Point<T>> _points;

    std::uint64_t _points_count;
};

#endif //MAI_OOP_2025_POLYGON_H

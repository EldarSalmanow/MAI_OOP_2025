#include <cstdint>

#include <lab3/figure.h>


Figure::Figure(std::uint64_t points_count)
        : _points(),
          _points_count(points_count) {
    _points.resize(_points_count);
}

Figure::Figure(const Figure &figure)
        : _points(figure._points),
          _points_count(figure._points_count) {}

Figure::Figure(Figure &&figure) noexcept
        : _points(std::move(figure._points)),
          _points_count(figure._points_count) {}

Figure::~Figure() noexcept = default;

Point Figure::CenterOfRotation() const {
    double x_average = 0.0, y_average = 0.0;

    for (std::uint64_t i = 0; i < _points_count; ++i) {
        x_average += _points[i].X();
        y_average += _points[i].Y();
    }

    return {
            x_average / static_cast<double>(_points_count),
            y_average / static_cast<double>(_points_count)
    };
}

std::istream &Figure::Input(std::istream &istream) {
    for (std::uint64_t i = 0; i < _points_count; ++i) {
        istream >> _points[i];
    }

    return istream;
}

std::ostream &Figure::Output(std::ostream &ostream) const {
    for (std::uint64_t i = 0; i < _points_count - 1; ++i) {
        ostream << _points[i] << " ";
    }

    ostream << _points[_points_count - 1] << std::endl;

    return ostream;
}

Figure &Figure::operator=(const Figure &figure) {
    if (this == &figure) {
        return *this;
    }

    if (_points_count != figure._points_count) {
        throw std::runtime_error("Figures with different points count!");
    }

    _points = figure._points;

    return *this;
}

Figure &Figure::operator=(Figure &&figure) noexcept {
    if (this == &figure) {
        return *this;
    }

    _points = std::move(figure._points);

    return *this;
}

bool Figure::operator==(const Figure &figure) const {
    if (_points.size() != figure._points.size()) {
        return false;
    }

    for (std::uint64_t i = 0; i < _points.size(); ++i) {
        if (_points[i] != figure._points[i]) {
            return false;
        }
    }

    return true;
}

bool Figure::operator!=(const Figure &figure) const {
    return !(*this == figure);
}

Figure::operator double() const {
    double x_y_sum = 0.0, y_x_sum = 0.0;

    for (uint64_t i = 0; i < _points_count - 1; ++i) {
        x_y_sum += _points[i].X() * _points[i + 1].Y();
        y_x_sum += _points[i].Y() * _points[i + 1].X();
    }

    x_y_sum += _points[_points_count - 1].X() * _points[0].Y(); // x_n * y_1
    y_x_sum += _points[_points_count - 1].Y() * _points[0].X(); // y_n * x_1

    return 0.5 * std::abs(x_y_sum - y_x_sum);
}

std::istream &operator>>(std::istream &istream, Figure &figure) {
    return figure.Input(istream);
}

std::ostream &operator<<(std::ostream &ostream, const Figure &figure) {
    return figure.Output(ostream);
}

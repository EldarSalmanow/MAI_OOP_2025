#include <cstdint>

#include <lab3/figure.h>


Figure::~Figure() noexcept = default;

std::istream &operator>>(std::istream &istream, Figure &figure) {
    return figure.Input(istream);
}

std::ostream &operator<<(std::ostream &ostream, const Figure &figure) {
    return figure.Output(ostream);
}

Point FigureCenterOfRotation(const Point *points,
                             std::uint64_t points_count) {
    double x_average = 0.0, y_average = 0.0;

    for (std::uint64_t i = 0; i < points_count; ++i) {
        x_average += points[i].X();
        y_average += points[i].Y();
    }

    return {
            x_average / static_cast<double>(points_count),
            y_average / static_cast<double>(points_count)
    };
}

double FigureArea(const Point *points,
                  std::uint64_t points_count) {
    double x_y_sum = 0.0, y_x_sum = 0.0;

    for (uint64_t i = 0; i < points_count - 1; ++i) {
        x_y_sum += points[i].X() * points[i + 1].Y();
        y_x_sum += points[i].Y() * points[i + 1].X();
    }

    x_y_sum += points[points_count - 1].X() * points[0].Y(); // x_n * y_1
    y_x_sum += points[points_count - 1].Y() * points[0].X(); // y_n * x_1

    return 0.5 * std::abs(x_y_sum - y_x_sum);
}

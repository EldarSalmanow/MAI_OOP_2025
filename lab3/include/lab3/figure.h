#ifndef MAI_OOP_2025_FIGURE_H
#define MAI_OOP_2025_FIGURE_H

#include <lab3/point.h>


class Figure {
public:

    virtual ~Figure() noexcept;

public:

    virtual Point CenterOfRotation() const = 0;

    virtual std::istream &Input(std::istream &istream) = 0;

    virtual std::ostream &Output(std::ostream &ostream) const = 0;

public:

    virtual operator double() const = 0;
};

std::istream &operator>>(std::istream &istream, Figure &figure);

std::ostream &operator<<(std::ostream &ostream, const Figure &figure);

Point FigureCenterOfRotation(const Point *points,
                             std::uint64_t points_count);

double FigureArea(const Point *points,
                  std::uint64_t points_count);

#endif //MAI_OOP_2025_FIGURE_H

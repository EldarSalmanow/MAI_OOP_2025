#ifndef MAI_OOP_2025_FIGURE_H
#define MAI_OOP_2025_FIGURE_H

#include <vector>

#include <lab3/point.h>


class Figure {
public:

    explicit Figure(std::uint64_t points_count);

    Figure(const Figure &figure);

    Figure(Figure &&figure) noexcept;

public:

    virtual ~Figure() noexcept;

public:

    virtual Point CenterOfRotation() const;

    virtual std::istream &Input(std::istream &istream);

    virtual std::ostream &Output(std::ostream &ostream) const;

public:

    Figure &operator=(const Figure &figure);

    Figure &operator=(Figure &&figure) noexcept;

    bool operator==(const Figure &figure) const;

    bool operator!=(const Figure &figure) const;

public:

    virtual operator double() const;

protected:

    std::vector<Point> _points;

    std::uint64_t _points_count;
};

std::istream &operator>>(std::istream &istream, Figure &figure);

std::ostream &operator<<(std::ostream &ostream, const Figure &figure);

#endif //MAI_OOP_2025_FIGURE_H

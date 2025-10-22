#ifndef MAI_OOP_2025_PENTAGON_H
#define MAI_OOP_2025_PENTAGON_H

#include <lab3/figure.h>


class Pentagon : public Figure {
public:

    Pentagon();

    Pentagon(const Pentagon &pentagon);

    Pentagon(Pentagon &&pentagon) noexcept;

public:

    Point CenterOfRotation() const override;

    std::istream &Input(std::istream &istream) override;

    std::ostream &Output(std::ostream &ostream) const override;

public:

    Pentagon &operator=(const Pentagon &pentagon);

    Pentagon &operator=(Pentagon &&pentagon) noexcept;

    bool operator==(const Pentagon &pentagon) const;

    operator double() const override;

private:

    static const std::uint64_t PointsCount = 5;

    Point _points[PointsCount];
};

std::istream &operator>>(std::istream &istream, Pentagon &pentagon);

std::ostream &operator<<(std::ostream &ostream, const Pentagon &pentagon);

#endif //MAI_OOP_2025_PENTAGON_H

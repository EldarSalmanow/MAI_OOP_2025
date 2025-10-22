#ifndef MAI_OOP_2025_HEXAGON_H
#define MAI_OOP_2025_HEXAGON_H

#include <lab3/figure.h>


class Hexagon : public Figure {
public:

    Hexagon();

    Hexagon(const Hexagon &hexagon);

    Hexagon(Hexagon &&hexagon) noexcept;

public:

    Point CenterOfRotation() const override;

    std::istream &Input(std::istream &istream) override;

    std::ostream &Output(std::ostream &ostream) const override;

public:

    Hexagon &operator=(const Hexagon &hexagon);

    Hexagon &operator=(Hexagon &&hexagon) noexcept;

    bool operator==(const Hexagon &hexagon) const;

    operator double() const override;

private:

    static const std::uint64_t PointsCount = 6;

    Point _points[PointsCount];
};

std::istream &operator>>(std::istream &istream, Hexagon &hexagon);

std::ostream &operator<<(std::ostream &ostream, const Hexagon &hexagon);

#endif //MAI_OOP_2025_HEXAGON_H

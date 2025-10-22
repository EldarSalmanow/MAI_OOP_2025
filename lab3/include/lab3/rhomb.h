#ifndef MAI_OOP_2025_RHOMB_H
#define MAI_OOP_2025_RHOMB_H

#include <lab3/figure.h>


class Rhomb : public Figure {
public:

    Rhomb();

    Rhomb(const Rhomb &rhomb);

    Rhomb(Rhomb &&rhomb) noexcept;

public:

    Point CenterOfRotation() const override;

    std::istream &Input(std::istream &istream) override;

    std::ostream &Output(std::ostream &ostream) const override;

public:

    Rhomb &operator=(const Rhomb &rhomb);

    Rhomb &operator=(Rhomb &&rhomb) noexcept;

    bool operator==(const Rhomb &rhomb) const;

    operator double() const override;

private:

    static const std::uint64_t PointsCount = 4;

    Point _points[PointsCount];
};

std::istream &operator>>(std::istream &istream, Rhomb &rhomb);

std::ostream &operator<<(std::ostream &ostream, const Rhomb &rhomb);

#endif //MAI_OOP_2025_RHOMB_H

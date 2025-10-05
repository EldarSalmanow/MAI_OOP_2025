#ifndef MAI_OOP_2025_FIGURE_H
#define MAI_OOP_2025_FIGURE_H

#include <iostream>

struct Point {
    double x, y;
};

class Figure {
public:

    virtual ~Figure() noexcept;

public:

    virtual std::pair<double, double> CenterOfRotation() const = 0;

public:

    virtual std::istream &operator>>(std::istream &istream) = 0;

    virtual std::ostream &operator<<(std::ostream &ostream) const = 0;

    virtual operator double() const = 0;
};

class Rhomb : public Figure {
public:

    Rhomb();

    Rhomb(const Rhomb &rhomb);

    Rhomb(Rhomb &&rhomb) noexcept;

public:

    std::pair<double, double> CenterOfRotation() const override;

public:

    Rhomb &operator=(const Rhomb &rhomb);

    Rhomb &operator=(Rhomb &&rhomb) noexcept;

    bool operator==(const Rhomb &rhomb) const;

    std::istream &operator>>(std::istream &istream) override;

    std::ostream &operator<<(std::ostream &ostream) const override;

    operator double() const override;

private:

    double _coordinates[8]; // (x, y) * 4
};

class Pentagon : public Figure {
public:

    Pentagon();

    Pentagon(const Pentagon &pentagon);

    Pentagon(Pentagon &&pentagon) noexcept;

public:

    std::pair<double, double> CenterOfRotation() const override;

public:

    Pentagon &operator=(const Pentagon &pentagon);

    Pentagon &operator=(Pentagon &&pentagon) noexcept;

    bool operator==(const Pentagon &pentagon) const;

    std::istream &operator>>(std::istream &istream) override;

    std::ostream &operator<<(std::ostream &ostream) const override;

    operator double() const override;

private:

    double _coordinates[10]; // (x, y) * 5
};

class Hexagon : public Figure {
public:

    Hexagon();

    Hexagon(const Hexagon &hexagon);

    Hexagon(Hexagon &&hexagon) noexcept;

public:

    std::pair<double, double> CenterOfRotation() const override;

public:

    Hexagon &operator=(const Hexagon &hexagon);

    Hexagon &operator=(Hexagon &&hexagon) noexcept;

    bool operator==(const Hexagon &hexagon) const;

    std::istream &operator>>(std::istream &istream) override;

    std::ostream &operator<<(std::ostream &ostream) const override;

    operator double() const override;

private:

    double _coordinates[12]; // (x, y) * 6
};

#endif //MAI_OOP_2025_FIGURE_H

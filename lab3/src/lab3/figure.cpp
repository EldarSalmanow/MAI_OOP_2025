#include <algorithm>
#include <cstdint>

#include <lab3/figure.h>


Figure::~Figure() noexcept = default;

Rhomb::Rhomb(const Rhomb &rhomb) {
    std::copy_n(rhomb._coordinates, 8, _coordinates);
}

Rhomb::Rhomb(Rhomb &&rhomb) noexcept {
    std::move(rhomb._coordinates, rhomb._coordinates + 8, _coordinates);
}

std::pair<double, double> Rhomb::CenterOfRotation() const {
    return {
        (_coordinates[0] - _coordinates[4]) / 2,
        (_coordinates[1] - _coordinates[5]) / 2
    };
}

Rhomb &Rhomb::operator=(const Rhomb &rhomb) {
    if (this == &rhomb) {
        return *this;
    }

    std::copy_n(rhomb._coordinates, 8, _coordinates);

    return *this;
}

Rhomb &Rhomb::operator=(Rhomb &&rhomb) noexcept {
    std::move(rhomb._coordinates, rhomb._coordinates + 8, _coordinates);

    return *this;
}

bool Rhomb::operator==(const Rhomb &rhomb) const {
    for (std::uint64_t i = 0; i < 8; ++i) {
        if (_coordinates[i] != rhomb._coordinates[i]) {
            return false;
        }
    }

    return true;
}

Rhomb::operator double() const {
    double x_y_sum = 0.0, y_x_sum = 0.0;

    for (uint64_t i = 0; i < 3; ++i) {
        x_y_sum += _coordinates[i * 2] * _coordinates[(i + 1) * 2 + 1];
        y_x_sum += _coordinates[i * 2 + 1] * _coordinates[(i + 1) * 2];
    }

    x_y_sum += _coordinates[3 * 2] * _coordinates[1]; // x_4 * y_1
    y_x_sum += _coordinates[3 * 2 + 1] * _coordinates[0]; // y_4 * x_1

    return 0.5 * std::abs(x_y_sum - y_x_sum);
}

Pentagon::Pentagon(const Pentagon &pentagon) {
    std::copy_n(pentagon._coordinates, 10, _coordinates);
}

Pentagon::Pentagon(Pentagon &&pentagon) noexcept {
    std::move(pentagon._coordinates, pentagon._coordinates + 10, _coordinates);
}

std::pair<double, double> Pentagon::CenterOfRotation() const {
    double x_average = 0.0, y_average = 0.0;

    for (std::uint64_t i = 0; i < 5; ++i) {
        x_average += _coordinates[i * 2];
        y_average += _coordinates[i * 2 + 1];
    }

    return {
            x_average / 5,
            y_average / 5
    };
}

Pentagon &Pentagon::operator=(const Pentagon &pentagon) {
    if (this == &pentagon) {
        return *this;
    }

    std::copy_n(pentagon._coordinates, 10, _coordinates);

    return *this;
}

Pentagon &Pentagon::operator=(Pentagon &&pentagon) noexcept {
    std::move(pentagon._coordinates, pentagon._coordinates + 10, _coordinates);

    return *this;
}

bool Pentagon::operator==(const Pentagon &pentagon) const {
    for (std::uint64_t i = 0; i < 10; ++i) {
        if (_coordinates[i] != pentagon._coordinates[i]) {
            return false;
        }
    }

    return true;
}

Pentagon::operator double() const {
    double x_y_sum = 0.0, y_x_sum = 0.0;

    for (uint64_t i = 0; i < 4; ++i) {
        x_y_sum += _coordinates[i * 2] * _coordinates[(i + 1) * 2 + 1];
        y_x_sum += _coordinates[i * 2 + 1] * _coordinates[(i + 1) * 2];
    }

    x_y_sum += _coordinates[4 * 2] * _coordinates[1]; // x_5 * y_1
    y_x_sum += _coordinates[4 * 2 + 1] * _coordinates[0]; // y_5 * x_1

    return 0.5 * std::abs(x_y_sum - y_x_sum);
}

Hexagon::Hexagon(const Hexagon &hexagon) {
    std::copy_n(hexagon._coordinates, 12, _coordinates);
}

Hexagon::Hexagon(Hexagon &&hexagon) noexcept {
    std::move(hexagon._coordinates, hexagon._coordinates + 12, _coordinates);
}

std::pair<double, double> Hexagon::CenterOfRotation() const {
    double x_average = 0.0, y_average = 0.0;

    for (std::uint64_t i = 0; i < 6; ++i) {
        x_average += _coordinates[i * 2];
        y_average += _coordinates[i * 2 + 1];
    }

    return {
        x_average / 6,
        y_average / 6
    };
}

Hexagon &Hexagon::operator=(const Hexagon &hexagon) {
    if (this == &hexagon) {
        return *this;
    }

    std::copy_n(hexagon._coordinates, 12, _coordinates);

    return *this;
}

Hexagon &Hexagon::operator=(Hexagon &&hexagon) noexcept {
    std::move(hexagon._coordinates, hexagon._coordinates + 12, _coordinates);

    return *this;
}

bool Hexagon::operator==(const Hexagon &hexagon) const {
    for (std::uint64_t i = 0; i < 12; ++i) {
        if (_coordinates[i] != hexagon._coordinates[i]) {
            return false;
        }
    }

    return true;
}

Hexagon::operator double() const {
    double x_y_sum = 0.0, y_x_sum = 0.0;

    for (uint64_t i = 0; i < 5; ++i) {
        x_y_sum += _coordinates[i * 2] * _coordinates[(i + 1) * 2 + 1];
        y_x_sum += _coordinates[i * 2 + 1] * _coordinates[(i + 1) * 2];
    }

    x_y_sum += _coordinates[5 * 2] * _coordinates[1]; // x_6 * y_1
    y_x_sum += _coordinates[5 * 2 + 1] * _coordinates[0]; // y_6 * x_1

    return 0.5 * std::abs(x_y_sum - y_x_sum);
}

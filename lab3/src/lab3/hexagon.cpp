#include <algorithm>
#include <cstdint>

#include <lab3/hexagon.h>


Hexagon::Hexagon() = default;

Hexagon::Hexagon(const Hexagon &hexagon) {
    std::copy_n(hexagon._points, PointsCount, _points);
}

Hexagon::Hexagon(Hexagon &&hexagon) noexcept {
    std::move(hexagon._points, hexagon._points + PointsCount, _points);
}

Point Hexagon::CenterOfRotation() const {
    return FigureCenterOfRotation(_points, PointsCount);
}

std::istream &Hexagon::Input(std::istream &istream) {
    for (std::uint64_t i = 0; i < PointsCount; ++i) {
        istream >> _points[i];
    }

    return istream;
}

std::ostream &Hexagon::Output(std::ostream &ostream) const {
    for (std::uint64_t i = 0; i < PointsCount - 1; ++i) {
        ostream << _points[i] << " ";
    }

    ostream << _points[PointsCount - 1] << std::endl;

    return ostream;;
}

Hexagon &Hexagon::operator=(const Hexagon &hexagon) {
    if (this == &hexagon) {
        return *this;
    }

    std::copy_n(hexagon._points, PointsCount, _points);

    return *this;
}

Hexagon &Hexagon::operator=(Hexagon &&hexagon) noexcept {
    if (this == &hexagon) {
        return *this;
    }

    std::move(hexagon._points, hexagon._points + PointsCount, _points);

    return *this;
}

bool Hexagon::operator==(const Hexagon &hexagon) const {
    for (std::uint64_t i = 0; i < PointsCount; ++i) {
        if (_points[i] != hexagon._points[i]) {
            return false;
        }
    }

    return true;
}

Hexagon::operator double() const {
    return FigureArea(_points, PointsCount);
}

std::istream &operator>>(std::istream &istream, Hexagon &hexagon) {
    return hexagon.Input(istream);
}

std::ostream &operator<<(std::ostream &ostream, const Hexagon &hexagon) {
    return hexagon.Output(ostream);
}

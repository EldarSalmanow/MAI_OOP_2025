#include <algorithm>
#include <cstdint>

#include <lab3/rhomb.h>

Rhomb::Rhomb() = default;

Rhomb::Rhomb(const Rhomb &rhomb) {
    std::copy_n(rhomb._points, PointsCount, _points);
}

Rhomb::Rhomb(Rhomb &&rhomb) noexcept {
    std::move(rhomb._points, rhomb._points + PointsCount, _points);
}

Point Rhomb::CenterOfRotation() const {
    return {
            (_points[1].X() - _points[3].X()) / 2,
            (_points[0].Y() - _points[2].Y()) / 2
    };
}

std::istream &Rhomb::Input(std::istream &istream) {
    for (std::uint64_t i = 0; i < Rhomb::PointsCount; ++i) {
        istream >> _points[i];
    }

    return istream;
}

std::ostream &Rhomb::Output(std::ostream &ostream) const {
    for (std::uint64_t i = 0; i < Rhomb::PointsCount - 1; ++i) {
        ostream << _points[i] << " ";
    }

    ostream << _points[Rhomb::PointsCount - 1] << std::endl;

    return ostream;
}

Rhomb &Rhomb::operator=(const Rhomb &rhomb) {
    if (this == &rhomb) {
        return *this;
    }

    std::copy_n(rhomb._points, PointsCount, _points);

    return *this;
}

Rhomb &Rhomb::operator=(Rhomb &&rhomb) noexcept {
    if (this == &rhomb) {
        return *this;
    }

    std::move(rhomb._points, rhomb._points + PointsCount, _points);

    return *this;
}

bool Rhomb::operator==(const Rhomb &rhomb) const {
    for (std::uint64_t i = 0; i < PointsCount; ++i) {
        if (_points[i] != rhomb._points[i]) {
            return false;
        }
    }

    return true;
}

Rhomb::operator double() const {
    return FigureArea(_points, PointsCount);
}

std::istream &operator>>(std::istream &istream, Rhomb &rhomb) {
    return rhomb.Input(istream);
}

std::ostream &operator<<(std::ostream &ostream, const Rhomb &rhomb) {
    return rhomb.Output(ostream);
}

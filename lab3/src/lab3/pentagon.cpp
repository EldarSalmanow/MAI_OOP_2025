#include <algorithm>
#include <cstdint>

#include <lab3/pentagon.h>


Pentagon::Pentagon() = default;

Pentagon::Pentagon(const Pentagon &pentagon) {
    std::copy_n(pentagon._points, PointsCount, _points);
}

Pentagon::Pentagon(Pentagon &&pentagon) noexcept {
    std::move(pentagon._points, pentagon._points + PointsCount, _points);
}

Point Pentagon::CenterOfRotation() const {
    return FigureCenterOfRotation(_points, PointsCount);
}

std::istream &Pentagon::Input(std::istream &istream) {
    for (std::uint64_t i = 0; i < PointsCount; ++i) {
        istream >> _points[i];
    }

    return istream;
}

std::ostream &Pentagon::Output(std::ostream &ostream) const {
    for (std::uint64_t i = 0; i < PointsCount - 1; ++i) {
        ostream << _points[i] << " ";
    }

    ostream << _points[PointsCount - 1] << std::endl;

    return ostream;;
}

Pentagon &Pentagon::operator=(const Pentagon &pentagon) {
    if (this == &pentagon) {
        return *this;
    }

    std::copy_n(pentagon._points, PointsCount, _points);

    return *this;
}

Pentagon &Pentagon::operator=(Pentagon &&pentagon) noexcept {
    if (this == &pentagon) {
        return *this;
    }

    std::move(pentagon._points, pentagon._points + PointsCount, _points);

    return *this;
}

bool Pentagon::operator==(const Pentagon &pentagon) const {
    for (std::uint64_t i = 0; i < PointsCount; ++i) {
        if (_points[i] != pentagon._points[i]) {
            return false;
        }
    }

    return true;
}

Pentagon::operator double() const {
    return FigureArea(_points, PointsCount);
}

std::istream &operator>>(std::istream &istream, Pentagon &pentagon) {
    return pentagon.Input(istream);
}

std::ostream &operator<<(std::ostream &ostream, const Pentagon &pentagon) {
    return pentagon.Output(ostream);
}

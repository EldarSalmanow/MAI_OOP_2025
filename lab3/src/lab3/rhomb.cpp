#include <algorithm>
#include <cstdint>

#include <lab3/rhomb.h>

Rhomb::Rhomb()
        : Figure(4) {}

Point Rhomb::CenterOfRotation() const {
    return {
            (_points[1].X() - _points[3].X()) / 2,
            (_points[0].Y() - _points[2].Y()) / 2
    };
}

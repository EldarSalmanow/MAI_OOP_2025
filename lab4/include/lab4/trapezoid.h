#ifndef MAI_OOP_2025_TRAPEZOID_H
#define MAI_OOP_2025_TRAPEZOID_H

#include <lab4/polygon.h>


template<typename T>
class Trapezoid : public Polygon<T> {
public:

    Trapezoid()
            : Polygon<T>(4) {}
};

#endif //MAI_OOP_2025_TRAPEZOID_H

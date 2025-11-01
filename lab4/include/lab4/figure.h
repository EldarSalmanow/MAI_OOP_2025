#ifndef MAI_OOP_2025_FIGURE_H
#define MAI_OOP_2025_FIGURE_H

#include <lab4/point.h>


template<typename T>
class Figure {
public:

    virtual ~Figure() noexcept = default;

public:

    virtual Point<T> CenterOfRotation() const = 0;

    virtual std::istream &Input(std::istream &istream) = 0;

    virtual std::ostream &Output(std::ostream &ostream) const = 0;

public:

    virtual operator T() const = 0;
};

template<typename T>
std::istream &operator>>(std::istream &istream,
                         Figure<T> &figure) {
    return figure.Input(istream);
}

template<typename T>
std::ostream &operator<<(std::ostream &ostream,
                         const Figure<T> &figure) {
    return figure.Output(ostream);
}

#endif //MAI_OOP_2025_FIGURE_H

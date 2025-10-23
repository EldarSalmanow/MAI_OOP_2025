#ifndef MAI_OOP_2025_RHOMB_H
#define MAI_OOP_2025_RHOMB_H

#include <lab3/figure.h>


class Rhomb : public Figure {
public:

    Rhomb();

public:

    Point CenterOfRotation() const override;
};

#endif //MAI_OOP_2025_RHOMB_H

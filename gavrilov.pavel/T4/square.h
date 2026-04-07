#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

class Square : public Rectangle {
public:
    Square(const Point& bottomLeft, double side);
    std::string getName() const override;
};

#endif

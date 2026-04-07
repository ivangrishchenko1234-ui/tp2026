#include "square.h"

Square::Square(const Point& bottomLeft, double side)
    : Rectangle(bottomLeft, Point(bottomLeft.x + side, bottomLeft.y + side)) {
}

std::string Square::getName() const {
    return "SQUARE";
}

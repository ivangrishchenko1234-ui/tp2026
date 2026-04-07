#include <iostream>
#include <string>
#include "Square.h"

Square::Square(const Point& bl, double sd) : bottomLeft(bl), side(sd) {
    isValid();
}

void Square::isValid() const {
    if (side <= 0) {
        throw std::invalid_argument("Square: side must be positive");
    }
}

double Square::getArea() const {
    return side*side;
}

Point Square::getCenter() const {
    double centerX = bottomLeft.x + side / 2.0;
    double centerY = bottomLeft.y + side / 2.0;
    return Point(centerX, centerY);
}

void Square::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;
}

void Square::scale(double fact) {
    if (fact <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    Point center = getCenter();
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * fact;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * fact;

    side = side * fact;
}

std::string Square::getName() const {
    return "SQUARE";
}

#include "square.h"

Square::Square(const Point& bl, double s) : bottomLeft(bl), side(s) {}

double Square::getArea() const {
    return side * side;
}
Point Square::getCenter() const {
    return Point(bottomLeft.x + side / 2.0, bottomLeft.y + side / 2.0);
}

void Square::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;
}

void Square::scale(double factor) {
    Point center = getCenter();
    side *= factor;
    bottomLeft.x = center.x - side / 2.0;
    bottomLeft.y = center.y - side / 2.0;
}

std::string Square::getName() const {
    return "SQUARE";
}
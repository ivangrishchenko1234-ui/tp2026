#include "rhombus.h"
#include <stdexcept>

Rhombus::Rhombus(const Point& center, double verticalDiagonal, double horizontalDiagonal)
    : center(center), verticalDiagonal(verticalDiagonal), horizontalDiagonal(horizontalDiagonal) {
    if (verticalDiagonal <= 0 || horizontalDiagonal <= 0) {
        throw std::invalid_argument("Diagonals must be positive");
    }
}

double Rhombus::getArea() const {
    return (verticalDiagonal * horizontalDiagonal) / 2.0;
}

Point Rhombus::getCenter() const {
    return center;
}

void Rhombus::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Rhombus::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    verticalDiagonal *= factor;
    horizontalDiagonal *= factor;
}

std::string Rhombus::getName() const {
    return "RHOMBUS";
}

BoundingBox Rhombus::getBoundingBox() const {
    BoundingBox box;
    box.bottomLeft = Point(center.x - horizontalDiagonal / 2, center.y - verticalDiagonal / 2);
    box.topRight = Point(center.x + horizontalDiagonal / 2, center.y + verticalDiagonal / 2);
    return box;
}

Point Rhombus::getTop() const {
    return Point(center.x, center.y + verticalDiagonal / 2.0);
}

Point Rhombus::getBottom() const {
    return Point(center.x, center.y - verticalDiagonal / 2.0);
}

Point Rhombus::getLeft() const {
    return Point(center.x - horizontalDiagonal / 2.0, center.y);
}

Point Rhombus::getRight() const {
    return Point(center.x + horizontalDiagonal / 2.0, center.y);
}

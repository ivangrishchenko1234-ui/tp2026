#include "rhombus.h"

Rhombus::Rhombus(const Point& c, double vd, double hd) {
    center = c;
    verticalDiagonal = vd;
    horizontalDiagonal = hd;
}

double Rhombus::getArea() const {
    return (verticalDiagonal * horizontalDiagonal) / 2.0;
}

Point Rhombus::getCenter() const {
    return center;
}

void Rhombus::move(double dx, double dy) {
    center.x_ += dx;
    center.y_ += dy;
}

void Rhombus::scale(double factor) {
    verticalDiagonal *= factor;
    horizontalDiagonal *= factor;
}

std::string Rhombus::getName() const {
    return "RHOMBUS";
}

#include "Rhombus.h"
#include <stdexcept>

Rhombus::Rhombus(const Point& c, double vertDiag, double horDiag)
    : center(c), verticalDiagonal(vertDiag), horizontalDiagonal(horDiag) {
    if (vertDiag <= 0 || horDiag <= 0) {
        throw std::invalid_argument("Diagonals must be positive");
    }
}

double Rhombus::getArea() const {
    return (verticalDiagonal * horizontalDiagonal) / 2.0;
}

void Rhombus::getBoundingBox(double& minX, double& minY, double& maxX, double& maxY) const {
    minX = center.x - verticalDiagonal / 2;
    maxX = center.x + verticalDiagonal / 2;
    minY = center.y - horizontalDiagonal / 2;
    maxY = center.y + horizontalDiagonal / 2;
}

Point Rhombus::getCenter() const {
    return center;
}

void Rhombus::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Rhombus::scale(double factor) {
    verticalDiagonal *= factor;
    horizontalDiagonal *= factor;
}

std::string Rhombus::getName() const {
    return "RHOMBUS";
}

double Rhombus::getVerticalDiagonal() const {
    return verticalDiagonal;
}

double Rhombus::getHorizontalDiagonal() const {
    return horizontalDiagonal;
}

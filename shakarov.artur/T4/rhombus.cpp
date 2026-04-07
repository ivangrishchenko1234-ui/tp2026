#include "rhombus.h"
#include <stdexcept>

Rhombus::Rhombus(const Point& center, double vertDiagonal, double horDiagonal)
    : center_(center), vertDiagonal_(vertDiagonal), horDiagonal_(horDiagonal) {
    if (vertDiagonal <= 0 || horDiagonal <= 0) {
        throw std::invalid_argument("Diagonals must be positive");
    }
}

double Rhombus::getArea() const {
    return (vertDiagonal_ * horDiagonal_) / 2.0;
}

Point Rhombus::getCenter() const {
    return center_;
}

void Rhombus::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}

void Rhombus::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    vertDiagonal_ *= factor;
    horDiagonal_ *= factor;
}

std::string Rhombus::getName() const {
    return "RHOMBUS";
}

#include "rhombus.h"
#include <string>

Rhombus::Rhombus(const Point& center, double diagonalVertical,
                 double diagonalHorizontal) :
                    center_(center),
                    diagonalVertical_(diagonalVertical),
                    diagonalHorizontal_(diagonalHorizontal)
                { }

double Rhombus::getArea() const {
    return (0.5 * diagonalVertical_ * diagonalHorizontal_);
}

Point Rhombus::getCenter() const {
    return center_;
}

void Rhombus::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}

void Rhombus::scale(double factor) {
    diagonalVertical_ *= factor;
    diagonalHorizontal_ *= factor;
}

std::string Rhombus::getName() const {
    return "RHOMBUS";
}

double Rhombus::getMinX() const {
    return center_.x - diagonalHorizontal_ / 2.0;
}

double Rhombus::getMinY() const {
    return center_.y - diagonalVertical_ / 2.0;
}

double Rhombus::getMaxX() const {
    return center_.x + diagonalHorizontal_ / 2.0;
}

double Rhombus::getMaxY() const {
    return center_.y + diagonalVertical_ / 2.0;
}

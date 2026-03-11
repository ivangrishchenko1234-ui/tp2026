#include "Ellipse.hpp"
#include <cmath>

Ellipse::Ellipse(const Point& c, double rx, double ry)
    : center_(c), radiusX_(rx), radiusY_(ry) {
}

double Ellipse::getArea() const {
    return 3.14159265358979323846 * radiusX_ * radiusY_;
}

Point Ellipse::getCenter() const {
    return center_;
}

void Ellipse::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}

void Ellipse::scale(double factor) {
    radiusX_ *= factor;
    radiusY_ *= factor;
}

std::string Ellipse::getName() const {
    return "ELLIPSE";
}

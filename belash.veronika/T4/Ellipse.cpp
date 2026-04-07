#include "Ellipse.hpp"
#include <cmath>
#include <stdexcept>

Ellipse::Ellipse(const Point& c, double rx, double ry)
    : center_(c), radiusX_(rx), radiusY_(ry) {
    if (rx <= 0 || ry <= 0) {
        throw std::invalid_argument("Ellipse radii cannot be negative");
    }
}

Shape::BoundingBox Ellipse::getBoundingBox() const {
    return {
        Point(center_.x - radiusX_, center_.y - radiusY_),
        Point(center_.x + radiusX_, center_.y + radiusY_)
    };
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

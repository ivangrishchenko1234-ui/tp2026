#include "circle.h"
#include <stdexcept>

Circle::Circle(const Point &center, double radius)
    : center_(center), radius_(radius) {
    if (radius <= 0.0) {
        throw std::invalid_argument("Radius must be positive");
    }
}

double Circle::getArea() const {
    const double PI = 3.14159265358979323846;
    return PI * radius_ * radius_;
}

Point Circle::getCenter() const {
    return center_;
}

void Circle::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}

void Circle::move(const Point &newCenter) {
    center_ = newCenter;
}

void Circle::scale(double factor) {
    if (factor <= 0.0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    radius_ *= factor;
}

std::string Circle::getName() const {
    return "CIRCLE";
}

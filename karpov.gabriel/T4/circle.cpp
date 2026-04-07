#include "circle.h"
#include <string>

const double PI = 3.14159;

Circle::Circle(const Point& center, double radius) :
        center_(center), radius_(radius)
    { }

double Circle::getArea() const {
    return PI * radius_ * radius_;
}

Point Circle::getCenter() const {
    return center_;
}

void Circle::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}

void Circle::scale(double factor) {
    radius_ *= factor;
}

std::string Circle::getName() const {
    return "CIRCLE";
}

double Circle::getMinX() const { return center_.x - radius_; }

double Circle::getMinY() const { return center_.y - radius_; }

double Circle::getMaxX() const { return center_.x + radius_; }

double Circle::getMaxY() const { return center_.y + radius_; }

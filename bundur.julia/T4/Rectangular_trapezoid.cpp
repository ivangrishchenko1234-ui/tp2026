#include "Rectangular_trapezoid.h"
#include <iostream>
RectangularTrapezoid::RectangularTrapezoid (Point bottomLeft, double baseLow, double baseUp, double height)
: bLow_(baseLow), bUp_(baseUp), h_(height) {
    center_.x = bottomLeft.x + (baseLow + baseUp) / 4.0;
    center_.y = bottomLeft.y + height / 2.0;
}
double RectangularTrapezoid::getArea() const {
    return 0.5 * (bLow_ + bUp_) * h_;
}
Point RectangularTrapezoid::getCenter() const {
    return center_;
}
void RectangularTrapezoid::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}
void RectangularTrapezoid::scale(double factor) {
    bLow_ *= factor;
    bUp_ *= factor;
    h_ *= factor;
}
std::string RectangularTrapezoid::getName() const {
    return "RIGHT TRAPEZOID";
}


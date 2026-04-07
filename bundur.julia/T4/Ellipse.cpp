#include <iostream>
#include "Ellipse.h"
#include <cmath>
Ellipse::Ellipse(Point center, double rx, double ry) : center_(center), rx_(rx), ry_(ry) {}
double Ellipse::getArea() const {
    return M_PI * rx_ * ry_;
}
Point Ellipse::getCenter() const {
    return center_;
}
void Ellipse::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}
void Ellipse::scale(double factor) {
    rx_ *= factor;
    ry_ *= factor;
}
std::string Ellipse::getName() const {
    return "ELLIPSE";
}


#include "Ellipse.h"
#include <iostream>
#include <string>
#include <cmath>
Ellipse::Ellipse(const Point& center, double rx, double ry)
    : center_(center), rx_(rx), ry_(ry) {}
double Ellipse::getArea() const {
    const double PI = 3.14159265358979323846;
    return PI * rx_ * ry_;
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
std::pair<Point, Point> Ellipse::getBounds() const {
    return {
        Point(center_.x - rx_, center_.y - ry_),
        Point(center_.x + rx_, center_.y + ry_)
    };
}

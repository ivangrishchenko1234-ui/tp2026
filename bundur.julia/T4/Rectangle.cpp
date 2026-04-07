#include "Rectangle.h"
#include <iostream>
#include <cmath>
Rectangle::Rectangle(Point bottomLeft, Point topRight) {
    width_ = std::abs(topRight.x - bottomLeft.x);
    height_ = std::abs(topRight.y - bottomLeft.y);
    center_ = {(bottomLeft.x + topRight.x) / 2.0, (bottomLeft.y + topRight.y) / 2.0};
}
double Rectangle::getArea() const {
    return width_ * height_;
}
Point Rectangle::getCenter() const {
    return center_;
}
void Rectangle::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}
void Rectangle::scale(double factor) {
    width_ *= factor;
    height_ *= factor;
}
std::string Rectangle::getName() const {
    return "RECTANGLE";
}


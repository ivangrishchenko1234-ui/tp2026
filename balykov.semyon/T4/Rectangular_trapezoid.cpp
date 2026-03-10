#include "rectangular_trapezoid.h"
#include <iostream>
#include <string>
Rectangular_trapezoid::Rectangular_trapezoid(const Point& bl,
    double lowerBase, double upperBase, double height)
    : bottomLeft(bl), lowerBase_(lowerBase),
    upperBase_(upperBase), height_(height) {}

double Rectangular_trapezoid::getArea() const {
    return ((lowerBase_ + upperBase_) / 2.0) * height_;
}
Point Rectangular_trapezoid::getCenter() const {
    double leftMidX = bottomLeft.x;
    double leftMidY = bottomLeft.y + (height_ / 2.0);
    double rightMidX = (bottomLeft.x + lowerBase_ + bottomLeft.x + upperBase_) / 2.0;

    double centerX = (leftMidX + rightMidX) / 2.0;
    double centerY = leftMidY;

    return Point(centerX, centerY);
}
void Rectangular_trapezoid::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;
}
void Rectangular_trapezoid::scale(double factor) {
    lowerBase_ *= factor;
    upperBase_ *= factor;
    height_ *= factor;
    Point center = getCenter();
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;
}

std::string Rectangular_trapezoid::getName() const {
    return "RECTANGULAR TRAPEZOID";
}
std::pair<Point, Point> Rectangular_trapezoid::getBounds() const {
    return { bottomLeft, Point(bottomLeft.x + lowerBase_,bottomLeft.y + height_) };
}
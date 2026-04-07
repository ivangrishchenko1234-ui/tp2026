#include "Rectangular_trapezoid.h"
#include <iostream>
#include <algorithm>
#include <string>
Rectangular_trapezoid::Rectangular_trapezoid(const Point& bl,
    double lowerBase, double upperBase, double height)
    : bottomLeft(bl), lowerBase_(lowerBase),
    upperBase_(upperBase), height_(height) {}

double Rectangular_trapezoid::getArea() const {
    return ((lowerBase_ + upperBase_) / 2.0) * height_;
}
Point Rectangular_trapezoid::getCenter() const {
    double centerX = bottomLeft.x + (lowerBase_ + upperBase_) / 4.0;
    double centerY = bottomLeft.y + height_ / 2.0;

    return Point(centerX, centerY);
}
void Rectangular_trapezoid::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;
}
void Rectangular_trapezoid::scale(double factor) {
    Point center = getCenter();
    lowerBase_ *= factor;
    upperBase_ *= factor;
    height_ *= factor;
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;
}

std::string Rectangular_trapezoid::getName() const {
    return "RECTANGULAR TRAPEZOID";
}
std::pair<Point, Point> Rectangular_trapezoid::getBounds() const {
    return std::make_pair(
        bottomLeft,
        Point(bottomLeft.x + std::max(lowerBase_, upperBase_),
            bottomLeft.y + height_
        )
    );
}

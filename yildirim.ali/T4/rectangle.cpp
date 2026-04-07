#include "rectangle.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

Rectangle::Rectangle(const Point& bl, const Point& tr) : bottomLeft(bl), topRight(tr) {
    if (bl.x >= tr.x || bl.y >= tr.y) {
        throw std::invalid_argument("Error: invalid rectangle coordinates");
    }
}
double Rectangle::getArea() const {
    double width = topRight.x - bottomLeft.x;
    double height = topRight.y - bottomLeft.y;
    return width * height;
}
Point Rectangle::getCenter() const {
    double centerX = (bottomLeft.x + topRight.x) / 2.0;
    double centerY = (bottomLeft.y + topRight.y) / 2.0;
    return Point(centerX, centerY);
}
void Rectangle::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;
    topRight.x += dx;
    topRight.y += dy;
}
void Rectangle::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("scale factor must be positive");
    }
    Point center = getCenter();
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;
    topRight.x = center.x + (topRight.x - center.x) * factor;
    topRight.y = center.y + (topRight.y - center.y) * factor;
}
std::string Rectangle::getName() const {
    return "RECTANGLE";
}
double Rectangle::getPerimeter() const {
    double width = topRight.x - bottomLeft.x;
    double height = topRight.y - bottomLeft.y;
    return 2 * (width + height);
}
bool Rectangle::containsPoint(const Point& p) const {
    return (p.x >= bottomLeft.x && p.x <= topRight.x &&
            p.y >= bottomLeft.y && p.y <= topRight.y);
}
void Rectangle::getBoundingBox(Point& min, Point& max) const {
    min = bottomLeft;
    max = topRight;
}
//

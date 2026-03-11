#include "Rectangle.h"
#include <iostream>
#include <string>
Rectangle::Rectangle(const Point& bl, const Point& tr) :
    bottomLeft(bl), topRight(tr) {}

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
    Point center = getCenter();
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;
    topRight.x = center.x + (topRight.x - center.x) * factor;
    topRight.y = center.y + (topRight.y - center.y) * factor;
}
std::string Rectangle::getName() const {
    return "RECTANGLE";
}
std::pair<Point, Point> Rectangle::getBounds() const {
    return { bottomLeft, topRight };
}

#include "rectangle.h"
#include <cmath>

Rectangle::Rectangle(const Point& bottomLeft, const Point& topRight)
    : bottomLeft(bottomLeft), topRight(topRight) {}

double Rectangle::getArea() const {
    double width = topRight.x - bottomLeft.x;
    double height = topRight.y - bottomLeft.y;
    return width * height;
}

Point Rectangle::getCenter() const {
    return Point((bottomLeft.x + topRight.x) / 2,
                 (bottomLeft.y + topRight.y) / 2);
}

void Rectangle::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;
    topRight.x += dx;
    topRight.y += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();
    bottomLeft.x = center.x - (center.x - bottomLeft.x) * factor;
    bottomLeft.y = center.y - (center.y - bottomLeft.y) * factor;
    topRight.x = center.x + (topRight.x - center.x) * factor;
    topRight.y = center.y + (topRight.y - center.y) * factor;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

BoundingBox Rectangle::getBoundingBox() const {
    BoundingBox box;
    box.bottomLeft = bottomLeft;
    box.topRight = topRight;
    return box;
}


#include "rectangle.h"
#include <string>

Rectangle::Rectangle(const Point& bottomLeft, const Point& topRight) :
        bottomLeft_(bottomLeft), topRight_(topRight)
    { }

double Rectangle::getArea() const {
    double width = topRight_.x - bottomLeft_.x;
    double height = topRight_.y - bottomLeft_.y;
    return width * height;
}

Point Rectangle::getCenter() const {
    double centerX = (topRight_.x + bottomLeft_.x) / 2.0;
    double centerY = (topRight_.y + bottomLeft_.y) / 2.0;
    return Point(centerX, centerY);
}

void Rectangle::move(double dx, double dy) {
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;
    topRight_.x += dx;
    topRight_.y += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();
    bottomLeft_.x = center.x + (bottomLeft_.x - center.x) * factor;
    bottomLeft_.y = center.y + (bottomLeft_.y - center.y) * factor;
    topRight_.x = center.x + (topRight_.x - center.x) * factor;
    topRight_.y = center.y + (topRight_.y - center.y) * factor;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

double Rectangle::getMinX() const { return bottomLeft_.x; }

double Rectangle::getMinY() const { return bottomLeft_.y; }

double Rectangle::getMaxX() const { return topRight_.x; }

double Rectangle::getMaxY() const { return topRight_.y; }

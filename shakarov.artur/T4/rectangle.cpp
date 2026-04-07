#include "rectangle.h"
#include <algorithm>
#include <cmath>

Rectangle::Rectangle(const Point& bl, const Point& tr)
    : bottomLeft_(bl), topRight_(tr) {}

double Rectangle::getArea() const {
    return getWidth() * getHeight();
}

Point Rectangle::getCenter() const {
    return Point((bottomLeft_.x + topRight_.x) / 2.0,
                 (bottomLeft_.y + topRight_.y) / 2.0);
}

void Rectangle::move(double dx, double dy) {
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;
    topRight_.x += dx;
    topRight_.y += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();
    bottomLeft_.x = center.x - (center.x - bottomLeft_.x) * factor;
    bottomLeft_.y = center.y - (center.y - bottomLeft_.y) * factor;
    topRight_.x = center.x + (topRight_.x - center.x) * factor;
    topRight_.y = center.y + (topRight_.y - center.y) * factor;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

double Rectangle::getWidth() const {
    return std::abs(topRight_.x - bottomLeft_.x);
}

double Rectangle::getHeight() const {
    return std::abs(topRight_.y - bottomLeft_.y);
}

#include "Rectangle.h"
#include <iostream>

double Rectangle::getArea() const {
    return (topRight.x - bottomLeft.x) * (topRight.y - bottomLeft.y);
}

Point Rectangle::getCenter() const {
    return Point((topRight.x + bottomLeft.x) / 2.0, (topRight.y + bottomLeft.y) / 2.0);
}

void Rectangle::move(double dx, double dy) {
    bottomLeft.x = bottomLeft.x + dx;
    bottomLeft.y = bottomLeft.y + dy;
    topRight.x = topRight.x + dx;
    topRight.y = topRight.y + dy;
}

void Rectangle::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Error: scale factor must be positive\n");
    }
    Point center = getCenter();
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;
    topRight.x = center.x + (topRight.x - center.x) * factor;
    topRight.y = center.y + (topRight.y - center.y) * factor;
}

std::string Rectangle::getName() const {
    return "Rectangle";
}

void Rectangle::info() const {
    std::cout << "[" << getName() << ", " << "(" << getCenter().x
        << ", " << getCenter().y << "), " << getArea() << "]" << '\n';
}

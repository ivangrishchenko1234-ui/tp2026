#include "Circle.h"
#include <iostream>

const double PI = 3.14159265;

double Circle::getArea() const {
    return PI * radius * radius;
}

Point Circle::getCenter() const {
    return center;
}

void Circle::move(double dx, double dy) {
    center.x = center.x + dx;
    center.y = center.y + dy;
}

void Circle::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Error: scale factor must be positive\n");
    }
    radius *= factor;
}

std::string Circle::getName() const {
    return "Circle";
}

void Circle::info() const {
    std::cout << "[" << getName() << ", " << "(" << getCenter().x
        << ", " << getCenter().y << "), " << getArea() << "]" << '\n';
}

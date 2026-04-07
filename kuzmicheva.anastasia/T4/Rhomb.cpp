#include "Rhomb.h"
#include <iostream>

double Rhomb::getArea() const {
    return (0.5 * vert * hor);
}

Point Rhomb::getCenter() const {
    return center;
}

void Rhomb::move(double dx, double dy) {
    center.x = center.x + dx;
    center.y = center.y + dy;
}

void Rhomb::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Error: scale factor must be positive\n");
    }
    vert *= factor;
    hor *= factor;
}

std::string Rhomb::getName() const {
    return "Rhomb";
}

void Rhomb::info() const {
    std::cout << "[" << getName() << ", " << "(" << getCenter().x
        << ", " << getCenter().y << "), " << getArea() << "]" << '\n';
}

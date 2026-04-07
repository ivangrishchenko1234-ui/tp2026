#include <iostream>
#include <string>
#include "Ellipse.h"

const double PI = 3.14159;

Ellipse::Ellipse(const Point& c, double rdx, double rdy) : center(c), radiusX(rdx), radiusY(rdy) {
    isValid();
}

void Ellipse::isValid() const {
    if (radiusX <= 0 || radiusY <= 0) {
        throw std::invalid_argument("Ellipse: radii must be positive");
    }
}

double Ellipse::getArea() const {
    return PI * radiusX * radiusY;
}

Point Ellipse::getCenter() const {
    return center;
}

void Ellipse::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Ellipse::scale(double fact) {
    if (fact <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    radiusX *= fact;
    radiusY *= fact;
}

std::string Ellipse::getName() const {
    return "ELLIPSE";
}

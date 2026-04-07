#include "square.h"
#include <stdexcept>

Square::Square(const Point &lowerLeft, double side) :
lowerLeft_(lowerLeft), side_(side) {
    if (side <= 0.0) {
        throw std::invalid_argument("Side must be positive");
    }
}

double Square::getArea() const { return side_ * side_; }

Point Square::getCenter() const {
    Point p;
    p.x = lowerLeft_.x + side_ / 2.0;
    p.y = lowerLeft_.y + side_ / 2.0;
    return p;
}

void Square::move(double dx, double dy) {
    lowerLeft_.x += dx;
    lowerLeft_.y += dy;
}

void Square::move(const Point &newCenter) {
    Point currentCenter = getCenter();
    move(newCenter.x - currentCenter.x, newCenter.y - currentCenter.y);
}

void Square::scale(double coefficient) {
    if (coefficient <= 0.0) {
        throw std::invalid_argument("Scale coefficient must be positive");
    }

    Point center = getCenter();
    side_ *= coefficient;
    lowerLeft_.x = center.x - side_ / 2.0;
    lowerLeft_.y = center.y - side_ / 2.0;
}

std::string Square::getName() const { return "SQUARE"; }

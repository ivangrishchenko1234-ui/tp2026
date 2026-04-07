#include "Square.h"
#include <stdexcept>
#include <memory>

Square::Square(const Point& bottomLeft, double side)
: bottomLeft_(bottomLeft), side_(side) {
}

double Square::getArea() const {
return side_ * side_;
}

Point Square::getCenter() const {
return Point(bottomLeft_.x + side_ / 2, bottomLeft_.y + side_ / 2);
}

void Square::move(double dx, double dy) {
bottomLeft_.x += dx;
bottomLeft_.y += dy;
}

void Square::scale(double factor) {
if (factor <= 0) {
throw std::invalid_argument("Scale factor must be positive.");
}

Point center = getCenter();
double newSide = side_ * factor;

bottomLeft_ = Point(center.x - newSide / 2, center.y - newSide / 2);
side_ = newSide;
}

std::string Square::getName() const {
return "SQUARE";
}

std::unique_ptr<Shape> Square::clone() const {
return std::make_unique<Square>(*this);
}

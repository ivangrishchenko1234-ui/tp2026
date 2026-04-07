#include "Square.h"
#include "Point.h"
#include <stdexcept>
#include <string>
#include <memory>

Square::Square(const Point& bottomLeft, double sideLength)
: bottomLeft_(bottomLeft), side_(sideLength) {

if (sideLength <= 0) {
throw std::invalid_argument("Error: Square side length must be positive.");
}
}

double Square::getArea() const {
return side_ * side_;
}

Point Square::getCenter() const {
return Point(bottomLeft_.x + side_ / 2.0,
bottomLeft_.y + side_ / 2.0);
}

void Square::move(double dx, double dy) {
bottomLeft_.x += dx;
bottomLeft_.y += dy;
}

void Square::scale(double factor) {
if (factor <= 0) {
throw std::invalid_argument("Error: Scale factor must be positive.");
}

Point center = getCenter();
side_ *= factor;
bottomLeft_.x = center.x - side_ / 2.0;
bottomLeft_.y = center.y - side_ / 2.0;
}

std::string Square::getName() const {
return "SQUARE";
}

std::unique_ptr<Shape> Square::clone() const {
return std::make_unique<Square>(*this);
}

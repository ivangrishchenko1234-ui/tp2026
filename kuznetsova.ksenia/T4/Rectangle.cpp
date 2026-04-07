#include "Rectangle.h"
#include "Point.h"
#include <stdexcept>
#include <string>
#include <memory>
#include <algorithm>

Rectangle::Rectangle(const Point& bottomLeft, const Point& topRight)
: bottomLeft(bottomLeft), topRight(topRight) {

double width = topRight.x - bottomLeft.x;
double height = topRight.y - bottomLeft.y;

if (width <= 0 || height <= 0) {
throw std::invalid_argument("Error: Rectangle width and height must be positive.");
}
}

double Rectangle::getArea() const {
return (topRight.x - bottomLeft.x) * (topRight.y - bottomLeft.y);
}

Point Rectangle::getCenter() const {
return Point((bottomLeft.x + topRight.x) / 2.0,
(bottomLeft.y + topRight.y) / 2.0);
}

void Rectangle::move(double dx, double dy) {
bottomLeft.x += dx;
bottomLeft.y += dy;
topRight.x += dx;
topRight.y += dy;
}

void Rectangle::scale(double factor) {
if (factor <= 0) {
throw std::invalid_argument("Error: Scale factor must be positive.");
}

Point center = getCenter();
bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;
topRight.x = center.x + (topRight.x - center.x) * factor;
topRight.y = center.y + (topRight.y - center.y) * factor;
}

std::string Rectangle::getName() const {
return "RECTANGLE";
}

std::unique_ptr<Shape> Rectangle::clone() const {
return std::make_unique<Rectangle>(*this);
}

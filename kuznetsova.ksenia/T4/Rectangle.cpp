#include "Rectangle.h"
#include <stdexcept>
#include <memory>
#include <algorithm>

Rectangle::Rectangle(const Point& p1, const Point& p2)
: bottomLeft_(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
topRight_(std::max(p1.x, p2.x), std::max(p1.y, p2.y)) {
}

double Rectangle::getArea() const {
return (topRight_.x - bottomLeft_.x) * (topRight_.y - bottomLeft_.y);
}

Point Rectangle::getCenter() const {
return Point(
(bottomLeft_.x + topRight_.x) / 2,
(bottomLeft_.y + topRight_.y) / 2
);
}

void Rectangle::move(double dx, double dy) {
bottomLeft_.x += dx;
bottomLeft_.y += dy;
topRight_.x += dx;
topRight_.y += dy;
}

void Rectangle::scale(double factor) {
if (factor <= 0) {
throw std::invalid_argument("Scale factor must be positive.");
}

Point center = getCenter();
double halfW = (topRight_.x - bottomLeft_.x) / 2 * factor;
double halfH = (topRight_.y - bottomLeft_.y) / 2 * factor;

bottomLeft_ = Point(center.x - halfW, center.y - halfH);
topRight_ = Point(center.x + halfW, center.y + halfH);
}

std::string Rectangle::getName() const {
return "RECTANGLE";
}

std::unique_ptr<Shape> Rectangle::clone() const {
return std::make_unique<Rectangle>(*this);
}

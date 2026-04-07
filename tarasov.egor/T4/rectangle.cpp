#include <string>
#include "point.h"
#include "rectangle.h"
#include <algorithm>

Rectangle::Rectangle(const Point& l, const Point& r) :
    l_(l),
    r_(r)
{
    if (!((l_.x  < r_.x && l_.y < r_.y) || (l_.x > r_.x && l_.y > r_.y))) {
        throw std::invalid_argument("Rectangle: invalid arguments");
    }
}
double Rectangle::getArea() const {
    return (r_.x - l_.x) * (r_.y - l_.y);
}
Point Rectangle::getCenter() const {
    return Point((r_.x + l_.x) / 2, (r_.y + l_.y) / 2);
}
std::string Rectangle::getName() const {
    return "RECTANGLE";
}
void Rectangle::move(double a, double b) {
    l_ = Point(l_.x + a, l_.y + b);
    r_ = Point(r_.x + a, r_.y + b);
}
void Rectangle::scale(double c) {
    if (c <= 0) {
        return;
    }
    Point center = getCenter();
    r_ = Point(center.x + (r_.x - center.x) * c,
               center.y + (r_.y - center.y) * c);
    l_ = Point(center.x + (l_.x - center.x) * c,
               center.y + (l_.y - center.y) * c);
}
void Rectangle::getBoundingBox(double& minX, double& minY,
                                double& maxX, double& maxY) const {
    minX = std::min(l_.x, r_.x);
    minY = std::min(l_.y, r_.y);
    maxX = std::max(l_.x, r_.x);
    maxY = std::max(l_.y, r_.y);
}

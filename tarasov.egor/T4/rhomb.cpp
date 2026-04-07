#include <string>
#include "point.h"
#include "rhomb.h"

Rhomb::Rhomb(const Point& center, double length, double width) :
    center_(center),
    length_(length),
    width_(width)
{
    if (length <= 0) {
        throw std::invalid_argument("Rhomb: invalid length");
    }
    if (width <= 0) {
        throw std::invalid_argument("Rhomb: invalid width");
    }
}

double Rhomb::getArea() const {
    return ((length_ * width_) / 2);
}
Point Rhomb::getCenter() const {
    return center_;
}
std::string Rhomb::getName() const {
    return "RHOMB";
}
void Rhomb::move(double a, double b) {
    center_ = Point(center_.x + a, center_.y + b);
}
void Rhomb::scale(double c) {
    if (c <= 0) {
        return;
    }
    length_ = length_ * c;
    width_ = width_ * c;
}
void Rhomb::getBoundingBox(double& minX, double& minY,
                            double& maxX, double& maxY) const {
    minX = center_.x - (length_ / 2);
    minY = center_.y - (width_ / 2);
    maxX = center_.x + (length_ / 2);
    maxY = center_.y + (width_ / 2);
}

#include "Ring.h"
#include <stdexcept>
#include <cmath>
#include <iostream>

Ring::Ring(const Point &c, double outerR, double innerR) : center_(c),
                                                           outerRadius_(outerR),
                                                           innerRadius_(innerR) {
    if (innerRadius_ >= outerRadius_ || innerRadius_ < 0 || outerRadius_ < 0)
        throw std::invalid_argument("Invalid radii");
}

double Ring::getArea() const {
    return M_PI * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
}

Point Ring::getCenter() const {
    return center_;
}

void Ring::move(double dx, double dy) {
    center_.x_ += dx;
    center_.y_ += dy;
}

void Ring::scale(double factor) {
    if (factor <= 0)
        throw std::invalid_argument("Scale factor must be positive");

    outerRadius_ *= factor;
    innerRadius_ *= factor;
}

std::string Ring::getName() const {
    return "RING";
}

void Ring::print() const {
    Point center = getCenter();
    std::cout << "  "
            << getName()
            << ", (" << center.x_ << ", " << center.y_ << "), "
            << getArea() << "\n";
}

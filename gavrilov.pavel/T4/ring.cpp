#include "ring.h"
#include <cmath>
#include <stdexcept>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Ring::Ring(const Point& center, double outerRadius, double innerRadius)
    : center_(center), outerRadius_(outerRadius), innerRadius_(innerRadius) {

    if (outerRadius_ <= 0 || innerRadius_ <= 0) {
        throw std::invalid_argument("Radii must be positive");
    }

    if (innerRadius_ >= outerRadius_) {
        throw std::invalid_argument("Inner radius must be less than outer radius");
    }
}

double Ring::getArea() const {
    return M_PI * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
}

Point Ring::getCenter() const {
    return center_;
}

void Ring::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}

void Ring::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    outerRadius_ *= factor;
    innerRadius_ *= factor;
}

std::string Ring::getName() const {
    return "RING";
}

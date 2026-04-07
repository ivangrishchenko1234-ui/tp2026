#include "Ring.h"
#include <cmath>
#include <string>
#include <stdexcept>

double constexpr PI = 3.1415;

double Ring::getArea() const {
    double sq = PI * (maxRad_ * maxRad_ - minRad_ * minRad_);
    return sq;
}

Point Ring::getCenter() const {
    return center_;
}

void Ring::move(double x, double y) {
    center_.x_ += x;
    center_.y_ += y;
}

void Ring::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Ring::scale: scale factor must be positive");
    }
    maxRad_ *= factor;
    minRad_ *= factor;
}

std::string Ring::getName() const {
    return "Ring";
}

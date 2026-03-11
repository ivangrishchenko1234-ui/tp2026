#include "ring.h"
#include <cmath>
#include <stdexcept>

const double MY_PI = 3.14159265358979323846;

Ring::Ring(const Point& c, double r, double R) : center_(c), innerR_(r), outerR_(R) {
    if (r <= 0 || R <= r) throw std::invalid_argument("Invalid ring radii");
}

double Ring::getArea() const {
    return MY_PI * (outerR_ * outerR_ - innerR_ * innerR_);
}

Point Ring::getCenter() const { return center_; }

void Ring::move(double dx, double dy) { center_.x += dx; center_.y += dy; }

void Ring::move(const Point& nc) { center_ = nc; }

void Ring::scale(double k) {
    if (k <= 0) throw std::invalid_argument("Scale k must be positive");
    innerR_ *= k;
    outerR_ *= k;
}

std::string Ring::getName() const { return "RING"; }

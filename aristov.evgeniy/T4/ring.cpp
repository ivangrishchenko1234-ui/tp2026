#include "ring.h"
#include "utils.h"
#include <stdexcept>
#include <cmath>

const double PI = std::acos(-1.0);

Ring::Ring(const Point& center, double rOuter, double rInner):
    center_(center),
    rOuter_(rOuter),
    rInner_(rInner) {
    if (rInner_ < 0.0 || rOuter_ <= rInner_) {
        throw std::invalid_argument("Invalid ring radii");
    }
}

double Ring::getArea() const {
    return PI * (rOuter_ * rOuter_ - rInner_ * rInner_);
}

Point Ring::getCenter() const {
    return center_;
}

void Ring::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}

void Ring::scale(double factor) {
    if (factor <= 0.0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    rOuter_ *= factor;
    rInner_ *= factor;
}

std::string Ring::getName() const {
    return "RING";
}

FrameRect Ring::getFrameRect() const {
    return {rOuter_ * 2.0, rOuter_ * 2.0, center_};
}

std::string Ring::toString() const {
    return formatShapeInfo(getName(), getCenter(), getArea());
}

std::unique_ptr<Shape> Ring::clone() const {
    return std::make_unique<Ring>(*this);
}

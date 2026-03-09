#include "right_trapezoid.h"
#include "utils.h"
#include <stdexcept>
#include <algorithm>

RightTrapezoid::RightTrapezoid(
    const Point& bottomLeft, double baseBottom, double baseTop, double height):
    bottomLeft_(bottomLeft),
    bottomBase_(baseBottom),
    topBase_(baseTop),
    height_(height) {
    if (bottomBase_ <= 0.0 || topBase_ <= 0.0 || height_ <= 0.0) {
        throw std::invalid_argument("Trapezoid dimensions must be positive");
    }
}

double RightTrapezoid::getArea() const {
    return ((bottomBase_ + topBase_) / 2.0) * height_;
}

Point RightTrapezoid::getCenter() const {
    return {bottomLeft_.x + (bottomBase_ + topBase_) / 4.0, bottomLeft_.y + height_ / 2.0};
}

void RightTrapezoid::move(double dx, double dy) {
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;
}

void RightTrapezoid::scale(double factor) {
    if (factor <= 0.0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    Point center = getCenter();
    bottomBase_ *= factor;
    topBase_ *= factor;
    height_ *= factor;

    bottomLeft_.x = center.x - (bottomBase_ + topBase_) / 4.0;
    bottomLeft_.y = center.y - height_ / 2.0;
}

std::string RightTrapezoid::getName() const {
    return "RIGHT_TRAPEZOID";
}

FrameRect RightTrapezoid::getFrameRect() const {
    double maxWidth = std::max(bottomBase_, topBase_);
    return {maxWidth, height_, {bottomLeft_.x + maxWidth / 2.0, getCenter().y}};
}

std::string RightTrapezoid::toString() const {
    return formatShapeInfo(getName(), getCenter(), getArea());
}

std::unique_ptr<Shape> RightTrapezoid::clone() const {
    return std::make_unique<RightTrapezoid>(*this);
}

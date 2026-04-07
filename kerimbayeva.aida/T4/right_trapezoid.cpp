#include "right_trapezoid.hpp"
#include <stdexcept>

RightTrapezoid::RightTrapezoid(const Point& left, double bottom, double top, double height)
    : left_(left), bottom_(bottom), top_(top), height_(height) {
    if (bottom <= 0 || top <= 0 || height <= 0) {
        throw std::invalid_argument("Bases and height must be positive");
    }
}

double RightTrapezoid::getArea() const {
    return (bottom_ + top_) / 2.0 * height_;
}

Point RightTrapezoid::getCenter() const {
    double centerX = left_.x + (bottom_ + top_) / 4.0;
    double centerY = left_.y + height_ / 2.0;
    return Point(centerX, centerY);
}

void RightTrapezoid::move(double dx, double dy) {
    left_.x += dx;
    left_.y += dy;
}

void RightTrapezoid::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }

    Point center = getCenter();

    bottom_ *= factor;
    top_ *= factor;
    height_ *= factor;

    left_.x = center.x - (bottom_ + top_) / 4.0;
    left_.y = center.y - height_ / 2.0;
}

std::string RightTrapezoid::getName() const {
    return "RIGHT_TRAPEZOID";
}

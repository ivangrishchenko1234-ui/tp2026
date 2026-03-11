#include "Right_trapezoid.hpp"

RightTrapezoid::RightTrapezoid(const Point& bl, double bBase, double tBase, double h)
    : bottomLeft_(bl), bottomBase_(bBase), topBase_(tBase), height_(h) {
}

double RightTrapezoid::getArea() const {
    return (bottomBase_ + topBase_) / 2.0 * height_;
}

Point RightTrapezoid::getCenter() const {
    double centerY = bottomLeft_.y + height_ / 2.0;
    double topOffset = (bottomBase_ - topBase_) / 2.0;
    double centerX = bottomLeft_.x + topOffset + topBase_ / 2.0;
    return Point(centerX, centerY);
}

void RightTrapezoid::move(double dx, double dy) {
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;
}

void RightTrapezoid::scale(double factor) {
    Point center = getCenter();

    double blX = bottomLeft_.x;
    double blY = bottomLeft_.y;

    bottomLeft_.x = center.x + (blX - center.x) * factor;
    bottomLeft_.y = center.y + (blY - center.y) * factor;

    bottomBase_ *= factor;
    topBase_ *= factor;
    height_ *= factor;
}

std::string RightTrapezoid::getName() const {
    return "RIGHT_TRAPEZOID";
}

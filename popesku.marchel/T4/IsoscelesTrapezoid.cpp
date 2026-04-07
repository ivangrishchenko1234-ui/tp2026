#include "IsoscelesTrapezoid.h"

#include <iostream>

IsoscelesTrapezoid::IsoscelesTrapezoid(const Point &bottomL, double bottomB, double topB,
                                       double h) : bottomLeft_(bottomL),
                                                   bottomBase_(bottomB),
                                                   topBase_(topB),
                                                   height_(h) {
    if (bottomB <= 0 || topB <= 0 || h <= 0)
        throw std::invalid_argument("Invalid trapezoid dimensions");
}

double IsoscelesTrapezoid::getArea() const {
    return (bottomBase_ + topBase_) / 2 * height_;
}

Point IsoscelesTrapezoid::getCenter() const {
    double centerX = bottomLeft_.x_ + bottomBase_ / 2;
    double centerY = bottomLeft_.y_ + height_ / 2;
    return Point(centerX, centerY);
}

void IsoscelesTrapezoid::move(double dx, double dy) {
    bottomLeft_.x_ += dx;
    bottomLeft_.y_ += dy;
}

void IsoscelesTrapezoid::scale(double factor) {
    if (factor <= 0)
        throw std::invalid_argument("Scale factor must be positive");

    Point center = getCenter();

    bottomLeft_.x_ = center.x_ + (bottomLeft_.x_ - center.x_) * factor;
    bottomLeft_.y_ = center.y_ + (bottomLeft_.y_ - center.y_) * factor;

    bottomBase_ *= factor;
    topBase_ *= factor;
    height_ *= factor;
}

std::string IsoscelesTrapezoid::getName() const {
    return "ISOSCELES_TRAPEZOID";
}

void IsoscelesTrapezoid::print() const {
    Point center = getCenter();
    std::cout << "  "
            << getName()
            << ", (" << center.x_ << ", " << center.y_ << "), "
            << getArea() << "\n";
}

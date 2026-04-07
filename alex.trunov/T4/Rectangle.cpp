#include "Rectangle.h"
#include <cmath>
#include <string>
#include <stdexcept>

double Rectangle::getArea() const {
    double width = std::abs(topRight_.x_ - bottomLeft_.x_);
    double height = std::abs(topRight_.y_ - bottomLeft_.y_);
    return width * height;
}

Point Rectangle::getCenter() const {
    double centerX = (topRight_.x_ - bottomLeft_.x_) / 2 + bottomLeft_.x_;
    double centerY = (topRight_.y_ - bottomLeft_.y_) / 2 + bottomLeft_.y_;
    return Point(centerX, centerY);
}

void Rectangle::move(double x, double y) {
    bottomLeft_.x_ += x;
    bottomLeft_.y_ += y;
    topRight_.x_ += x;
    topRight_.y_ += y;
}

void Rectangle::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Rectangle::scale: scale factor must be positive");
    }
    Point center = getCenter();
    bottomLeft_.x_ = center.x_ + (bottomLeft_.x_ - center.x_) * factor;
    bottomLeft_.y_ = center.y_ + (bottomLeft_.y_ - center.y_) * factor;
    topRight_.x_ = center.x_ + (topRight_.x_ - center.x_) * factor;
    topRight_.y_ = center.y_ + (topRight_.y_ - center.y_) * factor;
}

std::string Rectangle::getName() const {
    return "Rectangle";
}

#include "Square.h"

Point Square::getCenter() const {
    double centerX = (bl_.x_ + size_) / 2;
    double centerY = (bl_.y_ + size_) / 2;
    return Point(centerX, centerY);
}

void Square::move(double dx, double dy) {
    bl_.x_ += dx;
    bl_.y_ += dy;
}

void Square::scale(double factor) {
    Point center = getCenter();
    bl_.x_ = center.x_ + (bl_.x_ - center.x_) * factor;
    bl_.y_ = center.y_ + (bl_.y_ - center.y_) * factor;
    size_ *= factor;
}

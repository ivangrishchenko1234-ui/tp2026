#include "Rectangle.h"

void Rectangle::move(double dx, double dy) {
    bl_.x_ += dx;
    bl_.y_ += dy;
    tr_.x_ += dx;
    tr_.y_ += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();
    bl_.x_ = center.x_ + (bl_.x_ - center.x_) * factor;
    bl_.y_ = center.y_ + (bl_.y_ - center.y_) * factor;
    tr_.x_ = center.x_ + (tr_.x_ - center.x_) * factor;
    tr_.y_ = center.y_ + (tr_.y_ - center.y_) * factor;
    width_ *= factor;
    height_ *= factor;

}

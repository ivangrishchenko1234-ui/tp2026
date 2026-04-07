#include "Rectangle.h"

#include <iostream>

Rectangle::Rectangle(const Point &bl, const Point &tr) : bottomLeft_(bl),
                                                         topRight_(tr) {
    if (tr.x_ <= bl.x_ || tr.y_ <= bl.y_)
        throw std::invalid_argument("Invalid rectangle points");
}

double Rectangle::getArea() const {
    double width = topRight_.x_ - bottomLeft_.x_;
    double height = topRight_.y_ - bottomLeft_.y_;
    return width * height;
}

Point Rectangle::getCenter() const {
    double centerX = (bottomLeft_.x_ + topRight_.x_) / 2;
    double centerY = (bottomLeft_.y_ + topRight_.y_) / 2;
    return Point(centerX, centerY);
}

void Rectangle::move(double dx, double dy) {
    bottomLeft_.x_ += dx;
    bottomLeft_.y_ += dy;

    topRight_.x_ += dx;
    topRight_.y_ += dy;
}

void Rectangle::scale(double factor) {
    if (factor <= 0)
        throw std::invalid_argument("Scale factor must be positive");

    Point center = getCenter();

    bottomLeft_.x_ = center.x_ + (bottomLeft_.x_ - center.x_) * factor;
    bottomLeft_.y_ = center.y_ + (bottomLeft_.y_ - center.y_) * factor;

    topRight_.x_ = center.x_ + (topRight_.x_ - center.x_) * factor;
    topRight_.y_ = center.y_ + (topRight_.y_ - center.y_) * factor;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

void Rectangle::print() const {
    Point center = getCenter();
    std::cout << "  "
            << getName()
            << ", (" << center.x_ << ", " << center.y_ << "), "
            << getArea() << "\n";
}

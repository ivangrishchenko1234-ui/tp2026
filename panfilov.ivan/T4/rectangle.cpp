#include "rectangle.h"
#include <iostream>
#include <algorithm>

Rectangle::Rectangle(const Point& bl, const Point& tr) {
    if (bl.x_ >= tr.x_ || bl.y_ >= tr.y_) {
        throw std::invalid_argument("bottom left coordinate must be lower than top right");
    }
    bottomLeft = bl;
    topRight = tr;
}

double Rectangle::getArea() const {
    double width = topRight.x_ - bottomLeft.x_;
    double height = topRight.y_ - bottomLeft.y_;
    return width * height;
}

Point Rectangle::getCenter() const {
    double centerX = (bottomLeft.x_ + topRight.x_) / 2;
    double centerY = (bottomLeft.y_ + topRight.y_) / 2;
    return Point(centerX, centerY);
}

void Rectangle::move(double dx, double dy) {
    bottomLeft.x_ += dx;
    bottomLeft.y_ += dy;
    topRight.x_ += dx;
    topRight.y_ += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();
    bottomLeft.x_ = center.x_ + (bottomLeft.x_ - center.x_) * factor;
    bottomLeft.y_ = center.y_ + (bottomLeft.y_ - center.y_) * factor;
    topRight.x_ = center.x_ + (topRight.x_ - center.x_) * factor;
    topRight.y_ = center.y_ + (topRight.y_ - center.y_) * factor;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

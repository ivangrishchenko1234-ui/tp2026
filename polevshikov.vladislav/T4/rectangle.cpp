#include "rectangle.h"

Rectangle::Rectangle(const Point &lowerLeft, double width, double height) : 
lowerLeft_(lowerLeft), width_(width), height_(height) {
    if (width <= 0.0 || height <= 0.0) {
        throw std::invalid_argument("Width and height must be positive");
    }
}

double Rectangle::getArea() const { return width_ * height_; }

Point Rectangle::getCenter() const {
    Point p;
    p.x = lowerLeft_.x + width_ / 2.0;
    p.y = lowerLeft_.y + height_ / 2.0;
    return p;
}

void Rectangle::move(double dx, double dy) {
    lowerLeft_.x += dx;
    lowerLeft_.y += dy;
}

void Rectangle::move(const Point &newCenter) {
    Point currentCenter = getCenter();
    move(newCenter.x - currentCenter.x, newCenter.y - currentCenter.y);
}

void Rectangle::scale(double coefficient) {
    if (coefficient <= 0.0) {
    throw std::invalid_argument("Scale coefficient must be positive");
    } 

    Point center = getCenter();
    width_ *= coefficient;
    height_ *= coefficient;

    lowerLeft_.x = center.x - width_ / 2.0;
    lowerLeft_.y = center.y - height_ / 2.0;
}

std::string Rectangle::getName() const { return "RECTANGLE"; }
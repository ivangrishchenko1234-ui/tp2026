#include "rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const Point &bottomLeft, const Point &topRight)
    : bottomLeft_(bottomLeft), topRight_(topRight) {
    if (bottomLeft.x >= topRight.x || bottomLeft.y >= topRight.y) {
        throw std::invalid_argument("Invalid rectangle coordinates");
    }
}

double Rectangle::getArea() const {
    return (topRight_.x - bottomLeft_.x) * (topRight_.y - bottomLeft_.y);
}

Point Rectangle::getCenter() const {
    return {(bottomLeft_.x + topRight_.x) / 2.0, (bottomLeft_.y + topRight_.y) / 2.0};
}

void Rectangle::move(double dx, double dy) {
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;
    topRight_.x += dx;
    topRight_.y += dy;
}

void Rectangle::move(const Point &newCenter) {
    Point currentCenter = getCenter();
    move(newCenter.x - currentCenter.x, newCenter.y - currentCenter.y);
}

void Rectangle::scale(double factor) {
    if (factor <= 0.0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    Point center = getCenter();
    double width = (topRight_.x - bottomLeft_.x) * factor;
    double height = (topRight_.y - bottomLeft_.y) * factor;
    bottomLeft_ = {center.x - width / 2.0, center.y - height / 2.0};
    topRight_ = {center.x + width / 2.0, center.y + height / 2.0};
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

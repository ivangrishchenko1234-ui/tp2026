#include "rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const Point& bottomLeft, const Point& topRight)
    : bottomLeft_(bottomLeft), topRight_(topRight) {

    if (bottomLeft_.x >= topRight_.x || bottomLeft_.y >= topRight_.y) {
        throw std::invalid_argument("Bottom left must be left and below top right");
    }
}

double Rectangle::getArea() const {
    double width = topRight_.x - bottomLeft_.x;
    double height = topRight_.y - bottomLeft_.y;
    return width * height;
}

Point Rectangle::getCenter() const {
    return Point(
        (bottomLeft_.x + topRight_.x) / 2,
        (bottomLeft_.y + topRight_.y) / 2
    );
}

void Rectangle::move(double dx, double dy) {
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;
    topRight_.x += dx;
    topRight_.y += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();

    Point newBottomLeft(
        center.x + (bottomLeft_.x - center.x) * factor,
        center.y + (bottomLeft_.y - center.y) * factor
    );

    Point newTopRight(
        center.x + (topRight_.x - center.x) * factor,
        center.y + (topRight_.y - center.y) * factor
    );

    bottomLeft_ = newBottomLeft;
    topRight_ = newTopRight;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

#include "rectangle.h"
#include <stdexcept>
Rectangle::Rectangle(const Point& bl, const Point& tr) : bottomLeft(bl), topRight(tr) {
    if (bl.x >= tr.x || bl.x >= tr.y) {
        throw std::invalid_argument("rectangle: bottom-left must be less than top-right in both coordinates");
    }
}

double Rectangle::getArea() const {
    double width = topRight.x - bottomLeft.x;
    double height = topRight.y - bottomLeft.y;
    return width * height;
}

Point Rectangle::getCenter() const {
    double cx = (topRight.x + bottomLeft.x) / 2.0;
    double cy = (topRight.y + bottomLeft.y) / 2.0;
    return Point(cx, cy);
}

void Rectangle::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;
    topRight.x += dx;
    topRight.y += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();

    bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;
    topRight.x = center.x + (topRight.x - center.x) * factor;
    topRight.y = center.y + (topRight.y - center.y) * factor;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

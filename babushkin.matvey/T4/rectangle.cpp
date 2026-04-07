#include "rectangle.h"
#include <algorithm>
#include <stdexcept>

Rectangle::Rectangle(const Point& bl, const Point& tr) {
    double x1 = std::min(bl.x, tr.x);
    double x2 = std::max(bl.x, tr.x);
    double y1 = std::min(bl.y, tr.y);
    double y2 = std::max(bl.y, tr.y);

    if (x2 - x1 <= 0 || y2 - y1 <= 0) {
        throw std::invalid_argument("Rectangle: width and height must be positive");
    }

    bottomLeft = Point(x1, y1);
    topRight = Point(x2, y2);
}

double Rectangle::getArea() const {
    double width = topRight.x - bottomLeft.x;
    double height = topRight.y - bottomLeft.y;
    return width * height;
}

Point Rectangle::getCenter() const {
    double cx = (bottomLeft.x + topRight.x) / 2.0;
    double cy = (bottomLeft.y + topRight.y) / 2.0;
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

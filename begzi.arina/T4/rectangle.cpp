#include "rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(Point bl, Point tr) {
    if (tr.x <= bl.x || tr.y <= bl.y) {
        throw std::invalid_argument("Rectangle must have positive width and height");
    }
    bottomLeft = bl;
    topRight = tr;
}

double Rectangle::getArea() const {
    double width = topRight.x - bottomLeft.x;
    double height = topRight.y - bottomLeft.y;
    return width * height;
}

Point Rectangle::getCenter() const {
    double cx = (bottomLeft.x + topRight.x) / 2.0;
    double cy = (bottomLeft.y + topRight.y) / 2.0;
    return { cx, cy };
}

void Rectangle::move(double dx, double dy) {
    bottomLeft.x = bottomLeft.x + dx;
    bottomLeft.y = bottomLeft.y + dy;
    topRight.x = topRight.x + dx;
    topRight.y = topRight.y + dy;
}

void Rectangle::scale(double factor) {
    Point c = getCenter();
    bottomLeft.x = c.x + (bottomLeft.x - c.x) * factor;
    bottomLeft.y = c.y + (bottomLeft.y - c.y) * factor;
    topRight.x = c.x + (topRight.x - c.x) * factor;
    topRight.y = c.y + (topRight.y - c.y) * factor;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

void Rectangle::getBoundingBox(Point& bl, Point& tr) const {
    bl = bottomLeft;
    tr = topRight;
}

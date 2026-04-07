#include "Rectangle.h"
#include <stdexcept>
#include <algorithm>

Rectangle::Rectangle(const Point& bl, const Point& tr) :
    bottomLeft(bl),
    topRight(tr)
{
    if (bl.x >= tr.x || bl.y >= tr.y) {
        throw std::invalid_argument("Invalid rectangle coordinates: bottom-left must be below and left of top-right");
    }
}

double Rectangle::getArea() const {
    return getWidth() * getHeight();
}

void Rectangle::getBoundingBox(double& minX, double& minY, double& maxX, double& maxY) const {
    minX = std::min(bottomLeft.x, topRight.x);
    maxX = std::max(bottomLeft.x, topRight.x);
    minY = std::min(bottomLeft.y, topRight.y);
    maxY = std::max(bottomLeft.y, topRight.y);
}

Point Rectangle::getCenter() const {
    return Point((bottomLeft.x + topRight.x) / 2.0,
        (bottomLeft.y + topRight.y) / 2.0);
}

void Rectangle::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;
    topRight.x += dx;
    topRight.y += dy;
}

void Rectangle::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }

    Point center = getCenter();

    double halfWidth = getWidth() / 2.0 * factor;
    double halfHeight = getHeight() / 2.0 * factor;

    bottomLeft.x = center.x - halfWidth;
    bottomLeft.y = center.y - halfHeight;
    topRight.x = center.x + halfWidth;
    topRight.y = center.y + halfHeight;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

Point Rectangle::getBottomLeft() const {
    return bottomLeft;
}

Point Rectangle::getTopRight() const {
    return topRight;
}

double Rectangle::getWidth() const {
    return topRight.x - bottomLeft.x;
}

double Rectangle::getHeight() const {
    return topRight.y - bottomLeft.y;
}

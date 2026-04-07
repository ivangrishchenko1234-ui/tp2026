#include "circle.h"
#include <stdexcept>

Circle::Circle(Point c, double r) {
    if (r <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
    center = c;
    radius = r;
}

double Circle::getArea() const {
    return 3.14159265 * radius * radius;
}

Point Circle::getCenter() const {
    return center;
}

void Circle::move(double dx, double dy) {
    center.x = center.x + dx;
    center.y = center.y + dy;
}

void Circle::scale(double factor) {
    radius = radius * factor;
}

std::string Circle::getName() const {
    return "CIRCLE";
}

void Circle::getBoundingBox(Point& bl, Point& tr) const {
    bl.x = center.x - radius;
    bl.y = center.y - radius;
    tr.x = center.x + radius;
    tr.y = center.y + radius;
}

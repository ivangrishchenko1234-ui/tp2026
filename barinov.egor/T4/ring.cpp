#include "ring.h"
#include <cmath>
#include <stdexcept>

const double PI = 3.14159265358979323846;

Ring::Ring(const Point& center, double outerRadius, double innerRadius)
    : center(center), outerRadius(outerRadius), innerRadius(innerRadius) {
    if (innerRadius >= outerRadius) {
        throw std::invalid_argument("Inner radius must be less than outer radius");
    }
    if (innerRadius <= 0 || outerRadius <= 0) {
        throw std::invalid_argument("Radii must be positive");
    }
}

double Ring::getArea() const {
    return PI * (outerRadius * outerRadius - innerRadius * innerRadius);
}

Point Ring::getCenter() const {
    return center;
}

void Ring::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Ring::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    outerRadius *= factor;
    innerRadius *= factor;
}

std::string Ring::getName() const {
    return "RING";
}

BoundingBox Ring::getBoundingBox() const {
    BoundingBox box;
    box.bottomLeft = Point(center.x - outerRadius, center.y - outerRadius);
    box.topRight = Point(center.x + outerRadius, center.y + outerRadius);
    return box;
}


#include "ring.h"
#include <stdexcept>

Ring::Ring(const Point& c, double outer, double inner)
    : center(c), outerRadius(outer), innerRadius(inner) {
    if (outer <= 0.0 || inner <= 0.0) {
        throw std::invalid_argument("Ring: radii must be positive");
    }
    if (innerRadius >= outerRadius) {
        throw std::invalid_argument("Inner radius must be less than outer radius");
    }
}

double Ring::getArea() const {
    return 3.14 * (outerRadius * outerRadius - innerRadius * innerRadius);
}

Point Ring::getCenter() const {
    return center;
}

void Ring::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Ring::scale(double factor) {
    outerRadius *= factor;
    innerRadius *= factor;
}

std::string Ring::getName() const {
    return "RING";
}

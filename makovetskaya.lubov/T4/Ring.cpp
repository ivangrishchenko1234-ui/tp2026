#include "Ring.h"
#include <stdexcept>
#include <cmath>

Ring::Ring(const Point& c, double outerR, double innerR)
    : center(c), outerRadius(outerR), innerRadius(innerR) {
    if (outerR <= innerR) {
        throw std::invalid_argument("Outer radius must be greater than inner radius");
    }
    if (outerR <= 0 || innerR < 0) {
        throw std::invalid_argument("Radii must be positive");
    }
}

double Ring::getArea() const {
    const double PI = 3.14159265358979323846;
    return PI * (outerRadius * outerRadius - innerRadius * innerRadius);
}

void Ring::getBoundingBox(double& minX, double& minY,
    double& maxX, double& maxY) const {
    minX = center.x - outerRadius;
    maxX = center.x + outerRadius;
    minY = center.y - outerRadius;
    maxY = center.y + outerRadius;
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

double Ring::getOuterRadius() const {
    return outerRadius;
}

double Ring::getInnerRadius() const {
    return innerRadius;
}

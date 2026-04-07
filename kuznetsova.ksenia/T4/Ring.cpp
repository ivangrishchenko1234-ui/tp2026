#include "Ring.h"
#include <stdexcept>
#include <cmath>
#include <memory>

Ring::Ring(const Point& center, double outerRadius, double innerRadius)
    : center(center), outerRadius(outerRadius), innerRadius(innerRadius)
{
    if (outerRadius <= 0 || innerRadius < 0 || innerRadius >= outerRadius) {
        throw std::invalid_argument("Error: Invalid ring radii.");
    }
}

double Ring::getArea() const
{
    return M_PI * (outerRadius * outerRadius - innerRadius * innerRadius);
}

Point Ring::getCenter() const
{
    return center;
}

void Ring::move(double dx, double dy)
{
    center.x += dx;
    center.y += dy;
}

void Ring::scale(double factor)
{
    if (factor <= 0) {
        throw std::invalid_argument("Error: Scale factor must be positive.");
    }

    outerRadius *= factor;
    innerRadius *= factor;
}

std::string Ring::getName() const
{
    return "RING";
}

std::unique_ptr<Shape> Ring::clone() const
{
    return std::make_unique<Ring>(*this);
}

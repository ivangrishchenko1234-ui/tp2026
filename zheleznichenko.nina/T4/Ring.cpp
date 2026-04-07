#include "Ring.h"
#include <stdexcept>

const double PI = 3.1415926535;

Ring::Ring(Point c, double outerR, double innerR)
{
  if (outerR <= 0 || innerR <= 0) {
    throw std::invalid_argument("Radii must be positive");
  }
  if (innerR >= outerR) {
    throw std::invalid_argument("Inner radius must be less than outer radius");
  }
  center = c;
  outerRadius = outerR;
  innerRadius = innerR;
}

double Ring::getArea() const
{
  return PI * (outerRadius * outerRadius - innerRadius * innerRadius);
}

Point Ring::getCenter() const
{
  return center;
}

std::string Ring::getName() const
{
  return "RING";
}

void Ring::move(double dx, double dy)
{
  center.x += dx;
  center.y += dy;
}

void Ring::scale(double factor)
{
  if (factor <= 0) {
    throw std::invalid_argument("Scale factor must be positive");
  }
  outerRadius *= factor;
  innerRadius *= factor;
}

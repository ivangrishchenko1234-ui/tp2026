#include "IsoscelesTrapeziod.h"
#include <stdexcept>

IsoscelesTrapeziod::IsoscelesTrapeziod(Point bl, double bBase, double tBase, double h)
{
  if (bBase <= 0 || tBase <= 0 || h <= 0) {
    throw std::invalid_argument("Bases and height must be positive");
  }
  bottomLeft = bl;
  bottomBase = bBase;
  topBase = tBase;
  height = h;
}

double IsoscelesTrapeziod::getArea() const
{
  return (bottomBase + topBase) * height / 2.0;
}

Point IsoscelesTrapeziod::getCenter() const
{
  double midLineLength = (bottomBase + topBase) / 2.0;
  double offset = (bottomBase - topBase) / 2.0;
  double cx = bottomLeft.x + offset + midLineLength / 2.0;
  double cy = bottomLeft.y + height / 2.0;
  return Point(cx, cy);
}

std::string IsoscelesTrapeziod::getName() const
{
  return "ISOSCELESTRAPEZOID";
}

void IsoscelesTrapeziod::move(double dx, double dy)
{
  bottomLeft.x += dx;
  bottomLeft.y += dy;
}

void IsoscelesTrapeziod::scale(double factor)
{
  if (factor <= 0) {
    throw std::invalid_argument("Scale factor must be positive");
  }
  Point center = getCenter();
  bottomBase *= factor;
  topBase *= factor;
  height *= factor;
  Point newCenter = getCenter();
  bottomLeft.x += center.x - newCenter.x;
  bottomLeft.y += center.y - newCenter.y;
}

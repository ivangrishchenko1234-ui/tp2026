#include "Rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const Point& bl, const Point& tr)
{
  if (tr.x <= bl.x || tr.y <= bl.y) {
    throw std::invalid_argument("Invalid rectangle coordinates: topRight must be to the right and above bottomLeft");
  }
  bottomLeft = bl;
  topRight = tr;
}

double Rectangle::getArea() const
{
  double width = topRight.x - bottomLeft.x;
  double height = topRight.y - bottomLeft.y;
  return width * height;
}

Point Rectangle::getCenter() const
{
  double cx = (bottomLeft.x + topRight.x) / 2.0;
  double cy = (bottomLeft.y + topRight.y) / 2.0;
  return Point(cx, cy);
}

std::string Rectangle::getName() const
{
  return "RECTANGLE";
}

void Rectangle::move(double dx, double dy)
{
  bottomLeft.x += dx;
  bottomLeft.y += dy;

  topRight.x += dx;
  topRight.y += dy;
}

void Rectangle::scale(double factor)
{
  if (factor <= 0) {
    throw std::invalid_argument("Scale factor must be positive");
  }
  Point c = getCenter();

  bottomLeft.x = c.x + (bottomLeft.x - c.x) * factor;
  bottomLeft.y = c.y + (bottomLeft.y - c.y) * factor;

  topRight.x = c.x + (topRight.x - c.x) * factor;
  topRight.y = c.y + (topRight.y - c.y) * factor;
}

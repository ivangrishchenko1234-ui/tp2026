#include "CompositeShape.h"
#include <algorithm>
#include <limits>
#include <stdexcept>

void CompositeShape::addShape(std::unique_ptr< Shape > shape)
{
  if (!shape) {
    throw std::invalid_argument("Cannot add null shape");
  }
  shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const
{
  double sum = 0;

  for (const auto& s : shapes)
    sum += s->getArea();

  return sum;
}

Point CompositeShape::getCenter() const
{
  if (shapes.empty())
  {
    return Point(0, 0);
  }

  double minX = std::numeric_limits<double>::max();
  double minY = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double maxY = std::numeric_limits<double>::lowest();

  for (const auto& s : shapes)
  {
    Point c = s->getCenter();
    minX = std::min(minX, c.x);
    minY = std::min(minY, c.y);
    maxX = std::max(maxX, c.x);
    maxY = std::max(maxY, c.y);
  }

  return Point((minX + maxX) / 2.0, (minY + maxY) / 2.0);
}

std::string CompositeShape::getName() const
{
  return "CompositeShape";
}

void CompositeShape::move(double dx, double dy)
{
  for (auto& s : shapes)
    s->move(dx, dy);
}

void CompositeShape::scale(double factor)
{
  if (factor <= 0) {
    throw std::invalid_argument("Scale factor must be positive");
  }
  if (shapes.empty()) {
    return;
  }
  Point center = getCenter();

  for (auto& s : shapes)
  {
    Point sc = s->getCenter();

    double dx = sc.x - center.x;
    double dy = sc.y - center.y;

    double newDx = dx * factor;
    double newDy = dy * factor;

    double newX = center.x + newDx;
    double newY = center.y + newDy;

    s->move(newX - sc.x, newY - sc.y);

    s->scale(factor);
  }
}

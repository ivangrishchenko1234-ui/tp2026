#include <iostream>
#include <sstream>
#include <stdexcept>

#include "complex.h"


void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
  shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const
{
  double sum=0;
  size_t size=shapes_.size();
  for(size_t i = 0; i<size;i++){
    sum+=shapes_[i]->getArea();
  }
  return sum;
}

Point CompositeShape::getCenter() const
{
  size_t size = shapes_.size();
  if (size == 0) {
    return Point();
  }

  double sumX = 0.0;
  double sumY = 0.0;

  for (size_t i = 0; i < size; i++) {
    Point center = shapes_[i]->getCenter();
    sumX += center.x_;
    sumY += center.y_;
  }

  return Point(sumX / size, sumY / size);
}

void CompositeShape::move(double dx, double dy)
{
  size_t size=shapes_.size();
  for(size_t i=0;i<size;i++){
    shapes_[i]->move(dx,dy);
  }
}

void CompositeShape::scale(double factor)
{
  if (factor<=0) {
    throw std::invalid_argument("factor must be > 0");
  }
  Point center = getCenter();
  size_t size=shapes_.size();
  for (size_t i=0;i<size;i++) {
    Point shapeCenter = shapes_[i]->getCenter();
    Point offset = shapeCenter - center;
    offset.x_ *= factor;
    offset.y_ *= factor;
    Point newCenter = center + offset;
    shapes_[i]->move(
        newCenter.x_ - shapeCenter.x_,
        newCenter.y_ - shapeCenter.y_
    );
        shapes_[i]->scale(factor);
    }
}

std::string CompositeShape::getName() const
{
    return "CompositeShape";
}

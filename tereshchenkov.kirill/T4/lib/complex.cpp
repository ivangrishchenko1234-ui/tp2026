#include <iostream>
#include <sstream>

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
  size_t size=shapes_.size();
  if(size==0){
    return Point();
  }
  bool flag = true;
  double xma,xmi,yma,ymi;
  for(size_t i=0;i<size;i++){
    if (flag){
      xma=shapes_[i]->getCenter().x_;
      xmi=shapes_[i]->getCenter().x_;
      yma=shapes_[i]->getCenter().y_;
      ymi=shapes_[i]->getCenter().y_;
      flag = false;
    }
    if (xma < shapes_[i]->getCenter().x_) xma = shapes_[i]->getCenter().x_;
    else if(xmi > shapes_[i]->getCenter().x_) xmi = shapes_[i]->getCenter().x_;
    if (yma < shapes_[i]->getCenter().y_) yma = shapes_[i]->getCenter().y_;
    else if(ymi > shapes_[i]->getCenter().y_) ymi = shapes_[i]->getCenter().y_;
  }
  Rectangle a(Point(xmi,ymi), Point(xma,yma));
  return a.getCenter();
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

#include "trap.h"


Trap::Trap(const Point& bl, const double bottom, const double top, const double h) : bottomLeft_(bl), bottomLenght_(bottom), topLenght_(top), height_(h)
{
}

double Trap::getArea() const 
{
  return (topLenght_+bottomLenght_)/2*height_;
}

Point Trap::getCenter() const 
{
  const double xc = bottomLeft_.x_ + (bottomLenght_ + topLenght_) / 4.0;
  const double yc = bottomLeft_.y_ + height_ / 2.0;
  return Point(xc, yc);
}

void Trap::move(double dx, double dy)
{
  bottomLeft_+=Point(dx,dy);
}

void Trap::scale(double factor)
{
  Point center = getCenter();
  double halfTop= topLenght_/2;
  double halfBottom= bottomLenght_/2;
  halfBottom*=factor;
  halfTop*=factor;
  height_*=factor;
  bottomLenght_=halfBottom*2;
  topLenght_=halfTop*2;
  bottomLeft_.x_=center.x_-halfBottom;
  bottomLeft_.y_=center.y_-height_/2;
}

std::string Trap::getName() const 
{
  return "isosceles trapezoid";
}

#include "rectangle.h"

#include <stdexcept>


Rectangle::Rectangle(const Point& bl, const Point& tr) : bottomLeft(bl), topRight(tr)
{
  double width = topRight.x_ - bottomLeft.x_;
  double height = topRight.y_ - bottomLeft.y_;
  if (width <= 0 || height <= 0) {
    throw std::invalid_argument("Rectangle width and height must be positive");
  }
}

double Rectangle::getArea() const
{
  double width=topRight.x_-bottomLeft.x_;
  double height=topRight.y_-bottomLeft.y_;
  return width * height;
}

Point Rectangle::getCenter() const
{
  double cx=(topRight.x_+bottomLeft.x_)/2;
  double cy=(topRight.y_+bottomLeft.y_)/2;
  Point center(cx,cy);
  return(center);
}

void Rectangle::move(double dx, double dy)
{
  topRight.x_+=dx;
  topRight.y_+=dy;
  bottomLeft.x_+=dx;
  bottomLeft.y_+=dy;
}

void Rectangle::scale(double factor)
{
  if (factor<=0) {
    throw std::invalid_argument("factor must be > 0");
  }
  Point center=this->getCenter();
  Point rTop=topRight-center;
  Point rBot=bottomLeft-center;
  rTop.x_*=factor;
  rTop.y_*=factor;
  rBot.x_*=factor;
  rBot.y_*=factor;
  topRight=center+rTop;
  bottomLeft=center+rBot;
}

std::string Rectangle::getName() const
{
  return "Rectangle";
}

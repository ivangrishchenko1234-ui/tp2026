#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "shape.h"
#include "point.h"

class Rectangle: public Shape{
public:
  Rectangle(const Point& bl, const Point& tr);
   double getArea() const override;
   Point getCenter() const override;
   void move(double dx, double dy) override;
   void scale(double factor) override;
   std::string getName() const override;
private:
    Point bottomLeft;
    Point topRight;
};

#endif // _RECTANGLE_H_

#ifndef __TRAP_H__
#define __TRAP_H__

#include "shape.h"
#include "point.h"

class Trap: public Shape{
public:
  Trap(const Point& bl, const double bottom, const double top, const double h);
   double getArea() const override;
   Point getCenter() const override;
   void move(double dx, double dy) override;
   void scale(double factor) override;
   std::string getName() const override;
private:
    Point bottomLeft_;
    double topLenght_;
    double bottomLenght_;
    double height_;
};

#endif // __TRAP_H__

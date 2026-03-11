#ifndef __RING_H__
#define __RING_H__

#include "shape.h"
#include "point.h"

class Ring: public Shape{
public:
  Ring(const Point& center, const double r1,const double r2);
   double getArea() const override;
   Point getCenter() const override;
   void move(double dx, double dy) override;
   void scale(double factor) override;
   std::string getName() const override;
private:
    Point center_;
    double radiusBig_;
    double radiusSmall_; 
};

#endif // __RING_H__

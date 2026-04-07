#ifndef RING_H
#define RING_H
#include "Shape.h"

class Ring: public Shape
{
private:
  Point center;
  double outerRadius;
  double innerRadius;

public:
  Ring(Point c, double outerR, double innerR);

  double getArea() const override;
  Point getCenter() const override;

  void move(double dx, double dy) override;
  void scale(double factor) override;

  std::string getName() const override;
};
#endif

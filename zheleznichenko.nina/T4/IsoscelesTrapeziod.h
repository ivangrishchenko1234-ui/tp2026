#ifndef ISOSCELESTRAPEZIOD
#define ISOSCELESTRAPEZIOD
#include "Shape.h"

class IsoscelesTrapeziod: public Shape
{
private:
  Point bottomLeft;
  double bottomBase;
  double topBase;
  double height;

public:
  IsoscelesTrapeziod(Point bl, double bBase, double tBase, double h);

  double getArea() const override;
  Point getCenter() const override;

  void move(double dx, double dy) override;
  void scale(double factor) override;

  std::string getName() const override;
};
#endif

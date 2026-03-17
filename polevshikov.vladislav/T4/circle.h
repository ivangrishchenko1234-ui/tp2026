#pragma once

#include "shape.h"

class Circle : public Shape {
private:
  Point center_;
  double radius_;

public:
  Circle(const Point &center, double radius);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void move(const Point &newCenter) override;
  void scale(double coefficient) override;
  std::string getName() const override;
};
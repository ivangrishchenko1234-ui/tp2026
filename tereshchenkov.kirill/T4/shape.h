#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <string>
#include "point.h"

class Shape{
public:
  virtual ~Shape() = default;

  virtual double getArea() const = 0;
  virtual Point getCenter() const = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(double factor) = 0;
  virtual std::string getName() const = 0;
};

#endif // __SHAPE_H__

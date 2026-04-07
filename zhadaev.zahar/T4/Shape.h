#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include "Point.h"
class Shape
{
public:
    virtual double getArea() = 0;
    virtual Point getCenter() = 0;
    virtual void move(double x_, double y_) = 0;
    virtual void scale(double k) = 0;
    virtual std::string getName() = 0;
    virtual double getX_min() = 0;
    virtual double getX_max() = 0;
    virtual double getY_min() = 0;
    virtual double getY_max() = 0;
    virtual void print() = 0;
    virtual ~Shape() = default;
};
#endif

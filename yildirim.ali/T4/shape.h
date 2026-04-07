#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "point.h"

class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;
    virtual bool containsPoint(const Point& p) const = 0;
    virtual double getPerimeter() const = 0;
    virtual void getBoundingBox(Point& min, Point& max) const = 0;
};

#endif
//

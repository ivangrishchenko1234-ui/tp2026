#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <string>
#include <ostream>
#include "Point.h"

class Shape {
public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;
    virtual std::pair<Point, Point> getBounds() const = 0;
};
#endif

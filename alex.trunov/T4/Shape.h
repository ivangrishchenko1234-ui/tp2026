#include <iostream>
#include "Point.h"

#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double x, double y) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;

    virtual Point getTopRight() const = 0;
    virtual Point getBottomLeft() const = 0;
};

#endif // !SHAPE_H

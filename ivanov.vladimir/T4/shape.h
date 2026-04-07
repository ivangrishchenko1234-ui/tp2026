#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "point.h"

class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default;
    Shape(const Shape&) = default;
    Shape(Shape&&) = default;
    Shape& operator=(const Shape&) = default;
    Shape& operator=(Shape&&) = default;

    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const Point& newCenter) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;
};

#endif

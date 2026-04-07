#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"
#include <string>
#include <iostream>
#include <utility>


class Shape
{

public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual std::pair<Point, Point> Bounds() const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
        shape.print(os);
        return os;
    }
};


#endif

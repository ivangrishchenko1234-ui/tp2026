#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "Point.hpp"

class Shape {
public:
    struct BoundingBox {
        Point min;
        Point max;
    };
    virtual BoundingBox getBoundingBox() const = 0;
    virtual ~Shape() {}

    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;
};

#endif

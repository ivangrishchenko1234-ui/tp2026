#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "point.h"
#include <string>
#include <iostream>
#include <iomanip>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
        os << shape.getName() << ", (";
        Point c = shape.getCenter();
        os << std::fixed << std::setprecision(2) << c.x << ", " << c.y << "), ";
        os << std::fixed << std::setprecision(2) << shape.getArea();
        return os;
    }
};

#endif

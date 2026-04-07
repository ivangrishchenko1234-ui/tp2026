#ifndef SHAPE_H
#define SHAPE_H
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
    virtual void print() const {
        std::cout << "[" << getName() << ", (" << std::fixed << std::setprecision(2)
            << getCenter().x_ << ", " << getCenter().y_ << "), "
            << getArea() << "]\n";
    }
};

#endif

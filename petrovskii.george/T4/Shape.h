#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>
#include "Point.h"


struct Shape {
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double fact) = 0;
    virtual std::string getName() const = 0;

    virtual ~Shape() = default;
} ;


#endif // SHAPE_H

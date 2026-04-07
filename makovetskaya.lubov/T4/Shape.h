#ifndef SHAPE_H
#define SHAPE_H

#include "Point.h"
#include <string>

class Shape {
public:
    Shape() = default;
    virtual ~Shape() {}

    virtual double getArea() const = 0;
    virtual void getBoundingBox(double& minX, double& minY, double& maxX, double& maxY) const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;
};

#endif

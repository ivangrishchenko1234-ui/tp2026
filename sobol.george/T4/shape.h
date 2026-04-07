#ifndef SHAPE
#define SHAPE
#include <iostream>
#include <cstdlib>
#include <memory>
#include "point.h"

class Shape
{
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual std::string getName() const = 0;
    virtual void move(const double& factorX, const double& factorY) = 0;
    virtual void scale(const double& factor) = 0;

    virtual double getMinX() const = 0;
    virtual double getMaxX() const = 0;
    virtual double getMinY() const = 0;
    virtual double getMaxY() const = 0;
};
#endif

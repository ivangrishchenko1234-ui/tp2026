#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "point.h"

struct BoundingBox {
    Point bottomLeft;
    Point topRight;
    
    double getWidth() const { return topRight.x - bottomLeft.x; }
    double getHeight() const { return topRight.y - bottomLeft.y; }
    Point getCenter() const {
        return Point((bottomLeft.x + topRight.x) / 2,
                     (bottomLeft.y + topRight.y) / 2);
    }
};

class Shape {
public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;
    virtual BoundingBox getBoundingBox() const = 0;
};

#endif


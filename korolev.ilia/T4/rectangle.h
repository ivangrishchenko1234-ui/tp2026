#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(double leftX, double bottomY, double rightX, double topY);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    const char* getName() const override;

private:
    double leftX_;
    double bottomY_;
    double rightX_;
    double topY_;
};

#endif

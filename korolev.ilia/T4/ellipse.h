#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse(double centerX, double centerY, double radiusX, double radiusY);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    const char* getName() const override;

private:
    double centerX_;
    double centerY_;
    double radiusX_;
    double radiusY_;
};

#endif

#ifndef RECT_TRAPEZOID_H
#define RECT_TRAPEZOID_H

#include "shape.h"

class RectTrapezoid : public Shape
{
public:
    RectTrapezoid(double x, double y, double bottomBase, double topBase,
        double height);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    const char* getName() const override;

private:
    double bottomLeftX_;
    double bottomLeftY_;
    double bottomBase_;
    double topBase_;
    double height_;
};

#endif

#ifndef RECTANGULAR_TRAPEZOID_H
#define RECTANGULAR_TRAPEZOID_H
#include "Shape.h"
class RectangularTrapezoid : public Shape {
private:
    Point center_;
    double bLow_, bUp_, h_;
public:
    RectangularTrapezoid(Point bottomLeft, double baseLow, double baseUp, double height);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};
#endif



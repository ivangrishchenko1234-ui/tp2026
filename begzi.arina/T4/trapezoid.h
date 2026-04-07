#ifndef TRAPEZOID_H
#define TRAPEZOID_H
#include "shape.h"

class IsoscelesTrapezoid : public Shape {
private:
    Point bl;
    double bBase;
    double tBase;
    double height;

public:
    IsoscelesTrapezoid(Point p, double bb, double tb, double h);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    void getBoundingBox(Point& minP, Point& maxP) const override;
};

#endif

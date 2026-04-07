#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "shape.h"

class Trapezoid : public Shape {
private:
    Point bottomLeft;
    double bottomBase;
    double topBase;
    double height;
public:
    Trapezoid(const Point& bl, double bBase, double tBase, double h);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif

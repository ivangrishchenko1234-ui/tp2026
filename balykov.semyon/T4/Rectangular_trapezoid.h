#ifndef RECTANGULAR_TRAPEZOID_h
#define RECTANGULAR_TRAPEZOID_h

#include <iostream>
#include <string>
#include "shape.h"
class Rectangular_trapezoid : public Shape {
private:
    Point bottomLeft;
    double lowerBase_;
    double upperBase_;
    double height_;
public:
    Rectangular_trapezoid(const Point& bl, double lowerBase,
        double upperBase, double height);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> getBounds() const override;
};
#endif
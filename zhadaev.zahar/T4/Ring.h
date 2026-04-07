#ifndef RING_H
#define RING_H
#define PI 3.1415
#include "Shape.h"
#include<iostream>
class Ring : public Shape
{
public:
    Ring(Point dot, double R_, double r_);
    double getArea() override;
    Point getCenter() override;
    void move(double x_, double y_) override;
    void scale(double k) override;
    std::string getName() override;
    double getX_min() override;
    double getX_max() override;
    double getY_min() override;
    double getY_max() override;
    void print() override;
private:
    Point O;
    double R, r;
};
#endif

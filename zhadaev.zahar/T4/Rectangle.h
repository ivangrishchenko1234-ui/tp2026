#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <iostream>
#include "Shape.h"
class Rectangle : public Shape
{
public:
    Rectangle(Point A_, Point B_);
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
    Point A;
    Point B;
};
#endif

#include <iostream>
#include <string>
#include "Shape.h"
#include <stdexcept>

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public Shape {
public:
    Rectangle() = default;
    Rectangle(Point a, Point b) :
        bottomLeft_(a), topRight_(b)
    {
    }

    double getArea() const override;
    Point getCenter() const override;
    void move(double x, double y) override;
    void scale(double factor) override;
    std::string getName() const override;

    Point getTopRight() const override { return topRight_; }
    Point getBottomLeft() const override { return bottomLeft_; }
private:
    Point bottomLeft_, topRight_;
};

#endif

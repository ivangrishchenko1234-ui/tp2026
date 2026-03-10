#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <iostream>
#include <string>
#include "shape.h"
class Ellipse : public Shape {
private:
    Point center_;
    double rx_;
    double ry_;
public:
    Ellipse(const Point& center, double rx, double ry);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> getBounds() const override;
};
#endif

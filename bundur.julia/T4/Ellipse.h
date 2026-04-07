#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "Shape.h"
class Ellipse : public Shape {
private:
    Point center_;
    double rx_;
    double ry_;
public:
    Ellipse(Point center, double rx, double ry);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

};
#endif


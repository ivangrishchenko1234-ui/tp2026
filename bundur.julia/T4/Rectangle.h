#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
class Rectangle : public Shape {
private:
    Point center_;
    double width_, height_;
public:
    Rectangle(Point bottomLeft, Point topRight);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};
#endif


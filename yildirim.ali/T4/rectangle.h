#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
private:
    Point bottomLeft;
    Point topRight;

public:
    Rectangle(const Point& bl, const Point& tr);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    bool containsPoint(const Point& p) const override;
    double getPerimeter() const override;
    void getBoundingBox(Point& min, Point& max) const override;
};

#endif
//

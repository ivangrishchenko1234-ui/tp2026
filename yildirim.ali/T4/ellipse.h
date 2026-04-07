#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape {
private:
    Point center;
    double rx;
    double ry;
public:
    Ellipse(const Point& c, double r_x, double r_y);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    bool containsPoint(const Point& p) const override;
    double getPerimeter() const override;
    void getBoundingBox(Point& min, Point& max) const override;

    double getRx() const {
        return rx;
    }
    double getRy() const {
        return ry;
    }
};

#endif
//

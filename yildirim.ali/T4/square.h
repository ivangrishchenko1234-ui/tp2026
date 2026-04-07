#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape {
private:
    Point bottomLeft;
    double sideLength;
public:
    Square(const Point& bl, double side);
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

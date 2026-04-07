#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"
#include "Point.h"

class Square : public Shape
{
public:
    Square(const Point& bottomLeft, double sideLength);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::unique_ptr<Shape> clone() const override;

private:
    Point bottomLeft_;
    double side_;
};

#endif

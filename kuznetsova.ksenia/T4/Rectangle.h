#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "Point.h"
#include <memory>

class Rectangle : public Shape {
public:
Rectangle(const Point& p1, const Point& p2);

double getArea() const override;
Point getCenter() const override;
void move(double dx, double dy) override;
void scale(double factor) override;
std::string getName() const override;
std::unique_ptr<Shape> clone() const override;

private:
Point bottomLeft_;
Point topRight_;
};

#endif

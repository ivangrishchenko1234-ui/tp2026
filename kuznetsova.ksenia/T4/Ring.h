#ifndef RING_H
#define RING_H

#include "Shape.h"
#include "Point.h"
#include <memory>

class Ring : public Shape {
public:
Ring(const Point& center, double outRad, double inRad);

double getArea() const override;
Point getCenter() const override;
void move(double dx, double dy) override;
void scale(double factor) override;
std::string getName() const override;
std::unique_ptr<Shape> clone() const override;

private:
Point center;
double outerRadius, innerRadius;
};

#endif

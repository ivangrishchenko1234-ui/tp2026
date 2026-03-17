#ifndef RING_H
#define RING_H

#include "shape.h"

class Ring : public Shape {
private:
    Point center;
    double outerRadius;
    double innerRadius;
public:
    Ring(const Point& c, double outer, double inner);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif

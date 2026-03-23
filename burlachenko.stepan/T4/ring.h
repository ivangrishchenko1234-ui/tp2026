#ifndef RING_H
#define RING_H

#include "shape.h"

class Ring : public Shape
{
private:
    Point center_;
    double innerRadius_;
    double outerRadius_;
public:
    Ring(const Point& center, double rad1, double rad2);

    double getArea() const override;
    Point getCenter() const override;
    void move(const Point& newCenter) override;
    void scale(double ratio) override;
    std::string getName() const override;
};

#endif

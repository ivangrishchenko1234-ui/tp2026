#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
public:
    Circle(const Point &center, double radius);

    double getArea() const override;

    Point getCenter() const override;

    void move(double dx, double dy) override;

    void move(const Point &newCenter) override;

    void scale(double factor) override;

    std::string getName() const override;

private:
    Point center_;
    double radius_;
};

#endif

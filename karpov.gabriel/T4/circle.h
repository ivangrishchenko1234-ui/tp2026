#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
private:
    Point center_;
    double radius_;
public:
    Circle(const Point& center, double radius);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    double getMinX() const override;
    double getMinY() const override;
    double getMaxX() const override;
    double getMaxY() const override;
};

#endif

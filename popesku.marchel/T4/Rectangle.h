#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
public:
    Rectangle(const Point &bl, const Point &tr);

    double getArea() const override;

    Point getCenter() const override;

    void move(double dx, double dy) override;

    void scale(double factor) override;

    std::string getName() const override;

    void print() const override;

private:
    Point bottomLeft_;
    Point topRight_;
};

#endif

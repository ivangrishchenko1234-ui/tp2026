#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
private:
    Point lowerLeft_;
    double width_;
    double height_;

public:
    Rectangle(const Point &lowerLeft, double width, double height);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void move(const Point &newCenter) override;
    void scale(double coefficient) override;
    std::string getName() const override;
};

#endif

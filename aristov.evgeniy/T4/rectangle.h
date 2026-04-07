#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(const Point& bottomLeft, const Point& topRight);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    FrameRect getFrameRect() const override;
    std::string toString() const override;
    std::unique_ptr<Shape> clone() const override;

private:
    Point bottomLeft_;
    Point topRight_;
};

#endif

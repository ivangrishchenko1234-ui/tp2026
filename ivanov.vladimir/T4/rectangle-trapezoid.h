#ifndef RECTANGLE_TRAPEZOID_H
#define RECTANGLE_TRAPEZOID_H

#include "shape.h"

class RectangleTrapezoid : public Shape {
public:
    RectangleTrapezoid(const Point &bottomLeft, double bottomWidth,
                       double topWidth, double height);

    double getArea() const override;

    Point getCenter() const override;

    void move(double dx, double dy) override;

    void move(const Point &newCenter) override;

    void scale(double factor) override;

    std::string getName() const override;

private:
    Point bottomLeft_;
    double bottomWidth_;
    double topWidth_;
    double height_;
};

#endif

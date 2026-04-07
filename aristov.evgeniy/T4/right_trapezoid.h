#ifndef RIGHT_TRAPEZOID_H
#define RIGHT_TRAPEZOID_H

#include "shape.h"

class RightTrapezoid : public Shape {
public:
    RightTrapezoid(const Point& bottomLeft, double baseBottom, double baseTop, double height);

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
    double bottomBase_;
    double topBase_;
    double height_;
};

#endif

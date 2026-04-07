#ifndef RING_H
#define RING_H

#include "shape.h"

class Ring : public Shape {
public:
    Ring(const Point& center, double rOuter, double rInner);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    FrameRect getFrameRect() const override;
    std::string toString() const override;
    std::unique_ptr<Shape> clone() const override;

private:
    Point center_;
    double rOuter_;
    double rInner_;
};

#endif

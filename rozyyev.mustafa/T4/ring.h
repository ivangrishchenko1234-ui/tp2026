#ifndef RING_H
#define RING_H
#include "shape.h"

class Ring : public Shape {
public:
    Ring(const Point& center, double innerR, double outerR);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void move(const Point& newCenter) override;
    void scale(double k) override;
    std::string getName() const override;

    double getMinX() const override { return center_.x - outerR_; }
    double getMaxX() const override { return center_.x + outerR_; }
    double getMinY() const override { return center_.y - outerR_; }
    double getMaxY() const override { return center_.y + outerR_; }

private:
    Point center_;
    double innerR_, outerR_;
};
#endif

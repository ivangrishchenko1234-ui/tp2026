#ifndef TRAPEZOID_H
#define TRAPEZOID_H
#include "shape.h"

class Trapezoid : public Shape {
public:
    Trapezoid(const Point& bl, double a, double b, double h);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void move(const Point& nc) override;
    void scale(double k) override;
    std::string getName() const override;

    double getMinX() const override { return bl_.x; }
    double getMaxX() const override;
    double getMinY() const override { return bl_.y; }
    double getMaxY() const override { return bl_.y + h_; }

private:
    Point bl_;
    double a_, b_, h_;
};
#endif

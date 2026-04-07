#ifndef RIGHT_TRAPEZOID_HPP
#define RIGHT_TRAPEZOID_HPP

#include "shape.hpp"

class RightTrapezoid : public Shape {
private:
    Point left_;
    double bottom_;
    double top_;
    double height_;

public:
    RightTrapezoid(const Point& left, double bottom, double top, double height);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif

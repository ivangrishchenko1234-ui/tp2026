#ifndef RIGHT_TRAPEZOID_HPP
#define RIGHT_TRAPEZOID_HPP

#include "Shape.hpp"

class RightTrapezoid : public Shape {
private:
    Point bottomLeft_;
    double bottomBase_;
    double topBase_;
    double height_;

public:
    RightTrapezoid(const Point& bl, double bBase, double tBase, double h);
    ~RightTrapezoid() {}

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    Shape::BoundingBox getBoundingBox() const override;
};

#endif

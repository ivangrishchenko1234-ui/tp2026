#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "Shape.hpp"

class Ellipse : public Shape {
private:
    Point center_;
    double radiusX_;
    double radiusY_;

public:
    Ellipse(const Point& c, double rx, double ry);
    ~Ellipse() {}

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif

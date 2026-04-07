#ifndef ISOSCELES_TRAPEZOID_H
#define ISOSCELES_TRAPEZOID_H

#include "shape.h"

class IsoscelesTrapezoid : public Shape {
private:
    Point center_;
    double height_;
    double baseTop_;
    double baseBottom_;
public:
    IsoscelesTrapezoid(Point leftBottom, double baseBottom, double baseTop, double height);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double coeff) override;
    std::string getName() const override;
    RectanglePoints getBorderRectangle() const override;
};

#endif

#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "shape.h"

class Rhombus : public Shape {
private:
    Point center_;
    double diagonalVertical_;
    double diagonalHorizontal_;
public:
    Rhombus(const Point& center, double diagonalVertical,
            double diagonalHorizontal);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    double getMinX() const override;
    double getMinY() const override;
    double getMaxX() const override;
    double getMaxY() const override;
};

#endif

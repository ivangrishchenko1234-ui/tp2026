#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "shape.h"

class Rhombus : public Shape {
public:
    Rhombus(const Point& center, double vertDiagonal, double horDiagonal);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

private:
    Point center_;
    double vertDiagonal_;
    double horDiagonal_;
};

#endif

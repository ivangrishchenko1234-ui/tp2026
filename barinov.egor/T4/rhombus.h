#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "shape.h"

class Rhombus : public Shape {
private:
    Point center;
    double verticalDiagonal;
    double horizontalDiagonal;

public:
    Rhombus(const Point& center, double verticalDiagonal, double horizontalDiagonal);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    BoundingBox getBoundingBox() const override;

    Point getTop() const;
    Point getBottom() const;
    Point getLeft() const;
    Point getRight() const;
};

#endif


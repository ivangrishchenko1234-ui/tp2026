#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Shape.h"

class Rhombus : public Shape {
public:
    Rhombus(const Point& c, double vertDiag, double horDiag);

    double getArea() const override;
    void getBoundingBox(double& minX, double& minY, double& maxX, double& maxY) const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    double getVerticalDiagonal() const;
    double getHorizontalDiagonal() const;

private:
    Point center;
    double verticalDiagonal;
    double horizontalDiagonal;
};

#endif

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
public:
    Rectangle(const Point& bottomLeft, const Point& topRight);

    double getArea() const override;
    void getBoundingBox(double& minX, double& minY, double& maxX, double& maxY) const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    Point getBottomLeft() const;
    Point getTopRight() const;
    double getWidth() const;
    double getHeight() const;

private:
    Point bottomLeft;
    Point topRight;

};

#endif

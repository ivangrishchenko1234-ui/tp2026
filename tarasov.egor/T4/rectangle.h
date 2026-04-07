#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <string>
#include "point.h"
#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(const Point& l, const Point& r);
    double getArea() const override;
    Point getCenter() const override;
    void move(double a, double b) override;
    void scale(double c) override;
    std::string getName() const override;
    void getBoundingBox(double& minX, double& minY,
                        double& maxX, double& maxY) const override;
    Point getLeftBottom() const {
        return l_;
    }
    Point getRightTop() const {
        return r_;
    }
private:
    Point l_;
    Point r_;
};

#endif

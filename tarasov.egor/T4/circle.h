#ifndef CIRCLE_H
#define CIRCLE_H
#include <string>
#include "point.h"
#include "shape.h"

class Circle : public Shape {
public:
    Circle(const Point& center, double radius);
    double getArea() const override;
    Point getCenter() const override;
    void move(double a, double b) override;
    void scale(double c) override;
    std::string getName() const override;
    void getBoundingBox(double& minX, double& minY,
                        double& maxX, double& maxY) const override;

    double getRadius() const {
        return radius_;
    }
private:
    Point center_;
    double radius_;
};


#endif

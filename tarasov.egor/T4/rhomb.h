#ifndef RHOMB_H
#define RHOMB_H
#include <string>
#include "point.h"
#include "shape.h"

class Rhomb : public Shape {
public:
    Rhomb(const Point& center, double length, double width);
    double getArea() const override;
    Point getCenter() const override;
    void move(double a, double b) override;
    void scale(double c) override;
    std::string getName() const override;
    void getBoundingBox(double& minX, double& minY,
                        double& maxX, double& maxY) const override;

    double getLength() const {
        return length_;
    }
    double getWidth() const {
        return width_;
    }
private:
    Point center_;
    double length_;
    double width_;
};

#endif

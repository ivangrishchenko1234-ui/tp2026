#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "point.h"
#include "shape.h"
#include <string>
#include <cmath>

class Ellipse : public Shape {
private:
    Point center;
    double horizontal_radius;
    double vertical_radius;
public:
    Ellipse(const Point& center, double horizontal_radius, double vertical_radius);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    std::pair<Point, Point> getBounds() const override;
    void print(std::ostream& stream) const override;
};

#endif // ELLIPSE_H

#ifndef RECTANGULAR_TRAPEZOID_H
#define RECTANGULAR_TRAPEZOID_H

#include "point.h"
#include "shape.h"
#include <string>

class RectangularTrapezoid : public Shape {
private:
    Point bottomLeft;
    double bottomBase;
    double topBase;
    double height;

public:
    RectangularTrapezoid(const Point& bl, double bb, double tb, double h);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    double getMidlineLength() const;
    std::pair<Point, Point> getBounds() const override;
    void print(std::ostream& stream) const override;

};

#endif // RECTANGULAR_TRAPEZOID_H

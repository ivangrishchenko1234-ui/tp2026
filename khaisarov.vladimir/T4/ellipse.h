#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
private:
    Point centerE;
    double radiusHor;
    double radiusVer;

public:
    Ellipse(const Point& cen, double rh, double rv);
    double getArea() const override;
    Point getCenter() const override;
    std::string getName() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::pair<Point, Point> Bounds() const override;
    void print(std::ostream& os) const;
};

#endif

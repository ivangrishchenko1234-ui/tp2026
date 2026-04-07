#ifndef RECTTRAPEZOID_H
#define RECTTRAPEZOID_H

#include "shape.h"

class RectTrapezoid : public Shape
{

private:
    Point bLeft;
    double topLenght;
    double bottomLenght;
    double height;
public:
    RectTrapezoid(const Point& bl, double tlen, double blen, double h);
    double getArea() const override;
    std::string getName() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    std::pair<Point, Point> Bounds() const override;
    void scale(double factor) override;
    void print(std::ostream& os) const;
};

#endif

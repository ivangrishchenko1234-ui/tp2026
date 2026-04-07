#ifndef RIGHTTRAPEZOID_H
#define RIGHTTRAPEZOID_H
#include "shape.h"
#include "point.h"
#include <string>

class RightTrapezoid : public Shape
{
public:
    RightTrapezoid(const Point& bl, double bW, double tW, double h);
    ~RightTrapezoid() = default;
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> getFrame() const override;
private:
    Point bottomLeft;
    double bottomWidth;
    double topWidth;
    double height;
};

#endif

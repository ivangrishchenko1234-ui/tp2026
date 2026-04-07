#ifndef RECTANGULARTRAPEZOID_H
#define RECTANGULARTRAPEZOID_H
#include "Shape.h"
#include "Point.h"
#include <string>

class RectangularTrapezoid : public Shape
{
public:
    RectangularTrapezoid(const Point& bl, double bottomW, double topW, double h);
    ~RectangularTrapezoid() override = default;

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



#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
#include "Point.h"
#include <string>

class Circle : public Shape
{
public:
    Circle(const Point& ct, double rad);
    ~Circle() override = default;

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> getFrame() const override;

private:
    Point center;
    double radius;

    const double PI = 3.14;
};

#endif


#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"
#include "point.h"
#include <string>

class Circle : public Shape
{
public:
    Circle(const Point& ct, double rad);
    ~Circle() = default;
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> getFrame() const override;
private:
    Point center;
    double radius;
};

#endif

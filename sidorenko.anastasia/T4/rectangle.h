#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"
#include "point.h"
#include <string>


class Rectangle : public Shape
{
public:
    Rectangle(const Point& bl, const Point& tr);
    ~Rectangle() = default;
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> getFrame() const override;
private:
    Point bottomLeft;
    Point topRight;
};

#endif

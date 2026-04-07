#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include "Point.h"
#include <string>

class Rectangle : public Shape
{
private:
    Point bottomLeft;
    Point topRight;
public:
    Rectangle(const Point& bl, const Point& tr);
    ~Rectangle() override = default;

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> getFrame() const override;
};

#endif

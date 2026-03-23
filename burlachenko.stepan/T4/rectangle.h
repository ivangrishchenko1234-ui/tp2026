#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
private:
    Point corner1_;
    Point corner2_;
public:
    Rectangle(const Point& corner1, const Point& corner2);

    double getArea() const override;
    Point getCenter() const override;
    void move(const Point& newCenter) override;
    void scale(double ratio) override;
    std::string getName() const override;
};

#endif

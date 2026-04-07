#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include <string>
#include <utility>

class Rectangle : public Shape {
private:
    Point bottomLeft_;
    Point topRight_;

public:
    Rectangle(const Point& bl, const Point& tr);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> circumscribedRectangle() const override;
    void print(std::ostream& stream) const override;
};

#endif

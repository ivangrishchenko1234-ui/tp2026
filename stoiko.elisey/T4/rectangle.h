#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "shape.h"
#include <string>

class Rectangle : public Shape {
private:
    Point bottomLeft;
    Point topRight;
public:
    Rectangle(const Point& bl, const Point& rt);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    std::pair<Point, Point> getBounds() const override;
    void print(std::ostream& stream) const override;
};

#endif // RECTANGLE_H

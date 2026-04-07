#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(const Point& bl, const Point& tr);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void move(const Point& newCenter) override;
    void scale(double k) override;
    std::string getName() const override;

    double getMinX() const override { return bl_.x; }
    double getMaxX() const override { return tr_.x; }
    double getMinY() const override { return bl_.y; }
    double getMaxY() const override { return tr_.y; }

private:
    Point bl_, tr_;
};
#endif

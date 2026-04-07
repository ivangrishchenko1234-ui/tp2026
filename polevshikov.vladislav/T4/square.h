#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape {
private:
    Point lowerLeft_;
    double side_;
public:
    Square(const Point &lowerLeft, double side);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void move(const Point &newCenter) override;
    void scale(double coefficient) override;
    std::string getName() const override;
};

#endif

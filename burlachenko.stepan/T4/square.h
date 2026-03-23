#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape
{
private:
    Point corner_;
    double side_;

public:
    Square(const Point& corner, double side);

    double getArea() const override;
    Point getCenter() const override;
    void move(const Point& newCenter) override;
    void scale(double ratio) override;
    std::string getName() const override;
};

#endif

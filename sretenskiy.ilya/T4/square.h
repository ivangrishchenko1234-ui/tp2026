#ifndef SQUERE_H
#define SQUERE_H

#include "shape.h"

class Square : public Shape {
private:
    Point bottomLeft;
    double side;
public:
    Square(const Point& bl, double s);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif

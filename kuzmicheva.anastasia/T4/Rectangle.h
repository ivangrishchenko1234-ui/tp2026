#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <stdexcept>
#include "Shape.h"

class Rectangle : public Shape {
public:
    Rectangle(const Point& bl, const Point& tr) : bottomLeft(bl), topRight(tr) {
        if (tr.x <= bl.x || tr.y <= bl.y) {
            throw std::invalid_argument("Error: point number 2 must be top right!\n");
        }
    }
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    void info() const override;
private:
    Point bottomLeft;
    Point topRight;
};

#endif

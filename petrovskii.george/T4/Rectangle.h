#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include <string>
#include "Point.h"
#include "Shape.h"

class Rectangle : public Shape {
private:
    Point bottomLeft;
    Point topRight;

    void isValid() const;
public:
    Rectangle(const Point& bl, const Point& tr);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double fact) override;
    std::string getName() const override;
} ;

#endif // RECTANGLE_H

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <iostream>
#include <string>
#include "Point.h"
#include "Shape.h"

class Ellipse : public Shape {
private:
    Point center;
    double radiusX;
    double radiusY;

    void isValid() const;
public:
    Ellipse(const Point& center, double radiusX, double radiusY);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double fact) override;
    std::string getName() const override;
} ;

#endif // ELLIPSE_H

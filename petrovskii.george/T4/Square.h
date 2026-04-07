#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <string>
#include "Point.h"
#include "Shape.h"

class Square : public Shape {
private:
    Point bottomLeft;
    double side;

    void isValid() const;
public:
    Square(const Point& bl, double sd);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double fact) override;
    std::string getName() const override;
} ;

#endif // SQUARE_H

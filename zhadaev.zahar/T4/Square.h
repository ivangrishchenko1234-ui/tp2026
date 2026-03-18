#ifndef SQUARE_H
#define SQUARE_H
#include "Shape.h"
#include<iostream>
class Square : public Shape
{
public:
    Square(Point dot, double len);
    double getArea() override;
    Point getCenter() override;
    void move(double x_, double y_) override;
    void scale(double k) override;
    std::string getName() override;
    double getX_min() override;
    double getX_max() override;
    double getY_min() override;
    double getY_max() override;
    void print() override;
private:
    Point A;
    double length;
};
#endif

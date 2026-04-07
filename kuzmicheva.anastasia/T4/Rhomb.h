#ifndef RHOMB_H
#define RHOMB_H

#include <string>
#include <stdexcept>
#include "Shape.h"

class Rhomb : public Shape {
public:
    Rhomb(const Point& c, double v, double h) : center(c), vert(v), hor(h) {
        if ((v <= 0) || (h <= 0)) {
            throw std::invalid_argument("Error: diagonals must be positive!\n");
        }
    }
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    void info() const override;
private:
    Point center;
    double vert;
    double hor;
};

#endif

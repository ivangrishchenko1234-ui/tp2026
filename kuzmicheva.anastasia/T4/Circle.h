#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include <stdexcept>
#include "Shape.h"

class Circle : public Shape {
public:
    Circle(const Point& c, double r) : center(c), radius(r) {
        if (r <= 0) {
            throw std::invalid_argument("Error: radius must be positive!\n");
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
    double radius;
};

#endif

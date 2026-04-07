#ifndef RING_H
#define RING_H

#include "Shape.h"
#include <cmath>
#include <stdexcept>

class Ring : public Shape {
public:
    Ring() = delete;
    Ring(const Point& center, double radOut, double radIn) :
        center_(center),
        radiusOut_(radOut),
        radiusIn_(radIn) { // changed order of initialization
            if (radOut <= radIn) {
                throw std::invalid_argument("ERROR: Outer radius must be greater than in radius");
            }
            if (radIn < 0) {
                throw std::invalid_argument("ERROR: Radius cannot be negative");
            }
        }
    ~Ring() override = default;

    std::string getName() const override { return "Ring"; }
    double getArea() const override {
        return ((M_PI * radiusOut_ * radiusOut_) - (M_PI * radiusIn_ * radiusIn_));
    }
    Point getCenter() const override {
        return center_;
    }

    void move(double dx, double dy) override;
    void scale(double factor) override;

private:
    Point center_;
    double radiusOut_;
    double radiusIn_;
};

#endif

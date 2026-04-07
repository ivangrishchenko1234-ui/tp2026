#include <iostream>
#include <string>
#include "Point.h"
#include "Shape.h"
#include <stdexcept>

#ifndef RING_H
#define RING_H

class Ring : public Shape {
public:
    Ring() = default;
    Ring(double r1, double r2, Point p) {
        if (r1 < 0 || r2 < 0) {
            throw std::invalid_argument("Ring::Ring: radii cannot be negative");
        }
        if (r1 > r2) {
            throw std::invalid_argument("Ring::Ring: inner radius must be <= outer radius");
        }
        minRad_ = r1;
        maxRad_ = r2;
        center_ = p;
    }

    double getArea() const override;
    Point getCenter() const override;
    void move(double x, double y) override;
    void scale(double factor) override;
    std::string getName() const override;

    Point getTopRight() const override {
        Point p = getCenter();
        double rad = maxRad_;
        return Point(p.x_ + rad, p.y_ + rad);
    }
    Point getBottomLeft() const override {
        Point p = getCenter();
        double rad = maxRad_;
        return Point(p.x_ - rad, p.y_ - rad);
    }
private:
    double minRad_;
    double maxRad_;
    Point center_;
};

#endif

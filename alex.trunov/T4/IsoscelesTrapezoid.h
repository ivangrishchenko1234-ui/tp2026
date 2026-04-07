#include <iostream>
#include <string>
#include "Shape.h"
#include "Point.h"
#include <stdexcept>

#ifndef ISOSCELESTRAPEZOID_H
#define ISOSCELESTRAPEZOID_H

class IsoscelesTrapezoid : public Shape {
public:
    IsoscelesTrapezoid() = default;
    IsoscelesTrapezoid(Point bottomLeft, double bottomBase, double topBase, double height) {
        if (bottomBase <= 0 || topBase <= 0 || height <= 0) {
            throw std::invalid_argument("IsoscelesTrapezoid: bases and height must be positive");
        }
        bottomLeft_ = bottomLeft;
        bottomBase_ = bottomBase;
        topBase_ = topBase;
        height_ = height;
    }

    double getArea() const override;
    Point getCenter() const override;
    void move(double x, double y) override;
    void scale(double factor) override;
    std::string getName() const override;

    Point getTopRight() const override {
        Point p = bottomLeft_;
        return Point(p.x_ + bottomBase_, p.y_ + height_);
    }
    Point getBottomLeft() const override {
        return bottomLeft_;
    }
private:
    Point bottomLeft_;
    double bottomBase_;
    double topBase_;
    double height_;
};

#endif

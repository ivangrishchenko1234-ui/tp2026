#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"

#include <stdexcept>

class Square : public Shape {
public:
    Square() = delete;
    Square(const Point& bl, double size) : bl_(bl), size_(size) {
        if (size_ <= 0) { // changed condition
            throw std::invalid_argument("ERROR: Size cannot be less than 0");
        }
    }
    ~Square() override = default;

    Point getCenter() const override;
    double getArea() const override { return size_ * size_; }
    std::string getName() const override { return "Square"; }
    void move(double dx, double dy) override;
    void scale(double factor) override;

private:
    Point bl_;
    double size_;
};

#endif

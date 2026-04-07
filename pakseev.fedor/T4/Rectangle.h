#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

#include <stdexcept>

class Rectangle : public Shape {
public:
    Rectangle() = delete;
    Rectangle(const Point& bl, const Point& tr) : bl_(bl), tr_(tr) {
        if (bl_.x_ > tr_.x_ || bl_.y_ > tr_.y_) { // added validation check condition
            throw std::invalid_argument("ERROR: Bottom left point cant be > top right point");
        }
        width_ = tr_.x_ - bl_.x_;
        height_ = tr_.y_ - bl_.y_;
    };
    ~Rectangle() override = default;

    Point getCenter() const override {
        double centerX = (bl_.x_ + tr_.x_) / 2.0;
        double centerY = (bl_.y_ + tr_.y_) / 2.0;
        return Point(centerX, centerY);
    }

    std::string getName() const override { return "Rectangle"; }
    double getArea() const override { return width_ * height_; }
    void move(double dx, double dy) override;
    void scale(double factor) override;

private:
    Point bl_;
    Point tr_;
    double width_;
    double height_;
};

#endif

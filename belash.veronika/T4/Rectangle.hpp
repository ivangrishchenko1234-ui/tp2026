#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

class Rectangle : public Shape {
private:
    Point bottomLeft_;
    Point topRight_;

public:
    Rectangle(const Point& bl, const Point& tr);
    ~Rectangle() {}

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif

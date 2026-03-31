#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <iomanip>

class Shape {
public:
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double a, double b) = 0;
    virtual void scale(double c) = 0;
    virtual std::string getName() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
    os << "[" << shape.getName() << ", "
       << shape.getCenter() << ", "
       << shape.getArea() << "]";
    return os;
}
    virtual ~Shape() {};
};

#endif

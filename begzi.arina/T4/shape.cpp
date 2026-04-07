#include "shape.h"
#include <iostream>
#include <iomanip>

void Shape::print() const {
    Point center = getCenter();
    double area = getArea();
    std::string name = getName();

    std::cout << "[" << name << ", (";
    std::cout << std::fixed << std::setprecision(2) << center.x;
    std::cout << ", ";
    std::cout << std::fixed << std::setprecision(2) << center.y;
    std::cout << "), ";
    std::cout << std::fixed << std::setprecision(2) << area;
    std::cout << "]";
}

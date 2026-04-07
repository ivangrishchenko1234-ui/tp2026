#include "ellipse.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

Ellipse::Ellipse(const Point& c, double r_x, double r_y) : center(c), rx(r_x), ry(r_y) {
    if (r_x <= 0 || r_y <= 0) {
        throw std::invalid_argument("Error: radii must be positive");
    }
}
double Ellipse::getArea() const {
    return M_PI * rx * ry;
}
Point Ellipse::getCenter() const {
    return center;
}
void Ellipse::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}
void Ellipse::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("scale factor must be positive");
    }
    rx *= factor;
    ry *= factor;
}
std::string Ellipse::getName() const {
    return "ELLIPSE";
}
bool Ellipse::containsPoint(const Point& p) const {
    double dx = (p.x - center.x) / rx;
    double dy = (p.y - center.y) / ry;
    return (dx * dx + dy * dy) <= 1.0;
}
double Ellipse::getPerimeter() const {
    double sum = rx + ry;
    double h = ((rx - ry) * (rx - ry)) / (sum * sum);
    return M_PI * sum * (1 + (3 * h) / (10 + std::sqrt(4 - 3 * h)));
}
void Ellipse::getBoundingBox(Point& min, Point& max) const {
    min = Point(center.x - rx, center.y - ry);
    max = Point(center.x + rx, center.y + ry);
}
//

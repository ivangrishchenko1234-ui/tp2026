#include "Circle.h"
#include <stdexcept>

Circle::Circle(const Point& cent, double rad)
{
    if (rad <= 0.0)
    {
        throw std::invalid_argument("Circle radius must be positive");
    }
    center = cent;
    radius = rad;
}

double Circle::getArea() const {
    return PI * radius * radius;
}

Point Circle::getCenter() const {
    return center;
}

void Circle::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Circle::scale(double factor) {
    if (factor <= 0.0)
    {
        throw std::invalid_argument("Scale factor must be positive");
    }
    radius *= factor;
}

std::string Circle::getName() const {
    return "CIRCLE";
}

std::pair<Point, Point> Circle::getFrame() const {
    Point bottomLeft(center.x - radius, center.y - radius);
    Point topRight(center.x + radius, center.y + radius);
    return { bottomLeft, topRight };
}

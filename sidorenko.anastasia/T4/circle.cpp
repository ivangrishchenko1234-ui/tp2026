#include "circle.h"
#include <stdexcept>

const double PI = 3.14159265358979323846;

Circle::Circle(const Point& ct, double rad)
{
    if (rad <= 0)
    {
        throw std::invalid_argument("Uncorrect radius of circle\n");
    }
    center = ct;
    radius = rad;
}
double Circle::getArea() const
{
    return PI * radius * radius;
}
Point Circle::getCenter() const
{
    return center;
}
void Circle::move(double dx, double dy)
{
    center.x += dx;
    center.y += dy;
}
void Circle::scale(double factor)
{
    radius *= factor;
}
std::string Circle::getName() const
{
    return "CIRCLE";
}
std::pair<Point, Point> Circle::getFrame() const
{
    Point bottomLeft(center.x - radius, center.y - radius);
    Point topRight(center.x + radius, center.y + radius);
    return { bottomLeft, topRight };
}


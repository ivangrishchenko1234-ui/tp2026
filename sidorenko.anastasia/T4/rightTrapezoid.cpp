#include "rightTrapezoid.h"
#include <stdexcept>

RightTrapezoid::RightTrapezoid(const Point& bl, double bW, double tW, double h)
{
    if (bW <= 0 || tW <= 0 || h <= 0)
    {
        throw std::invalid_argument("Uncorrect arguments for right trapezoid\n");
    }
    bottomLeft = bl;
    bottomWidth = bW;
    topWidth = tW;
    height = h;
}
double RightTrapezoid::getArea() const
{
    return ((bottomWidth + topWidth) / 2.0) * height;
}
Point RightTrapezoid::getCenter() const
{
    double centerX = bottomLeft.x + (bottomWidth + topWidth) / 4.0;
    double centerY = bottomLeft.y + height / 2.0;
    return Point(centerX, centerY);
}
void RightTrapezoid::move(double dx, double dy)
{
    bottomLeft.x += dx;
    bottomLeft.y += dy;
}
void RightTrapezoid::scale(double factor)
{
    Point center = getCenter();
    bottomWidth *= factor;
    topWidth *= factor;
    height *= factor;
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;

}
std::string RightTrapezoid::getName() const
{
    return "RIGHT TRAPEZOID";
}
std::pair<Point, Point> RightTrapezoid::getFrame() const
{
    double minX = bottomLeft.x;
    double maxX = bottomLeft.x + std::max(bottomWidth, topWidth);
    double minY = bottomLeft.y;
    double maxY = bottomLeft.y + height;
    return { Point(minX, minY), Point(maxX, maxY) };
}

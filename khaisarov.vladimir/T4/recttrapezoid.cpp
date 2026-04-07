#include "recttrapezoid.h"
#include <algorithm>

RectTrapezoid::RectTrapezoid(const Point& bl, double tlen, double blen, double h) :
    bLeft(bl),
    topLenght(tlen),
    bottomLenght(blen),
    height(h)
{

}

double RectTrapezoid::getArea() const
{
    return ((topLenght + bottomLenght) / 2.0) * height;
}

std::string RectTrapezoid::getName() const
{
    return "RECTANGULAR TRAPEZOID";
}

void RectTrapezoid::move(double dx, double dy)
{
    bLeft.x += dx;
    bLeft.y += dy;
}

Point RectTrapezoid::getCenter() const
{
    double centerX = bLeft.x + ((topLenght + bottomLenght) / 4.0);
    double centerY = bLeft.y + height / 2.0;
    return Point(centerX, centerY);
}

std::pair<Point, Point> RectTrapezoid::Bounds() const
{
    Point lb = bLeft;
    double maxWidth = std::max(topLenght, bottomLenght);
    Point tr = Point(bLeft.x + maxWidth, bLeft.y + height);
    return std::make_pair(lb, tr);
}

void RectTrapezoid::scale(double factor)
{
    Point center = getCenter();
    bLeft.x = center.x - (center.x - bLeft.x) * factor;
    bLeft.y = center.y - (center.y - bLeft.y) * factor;
    height *= factor;
    topLenght *= factor;
    bottomLenght *= factor;
}

void RectTrapezoid::print(std::ostream& os) const
{
    os << std::fixed << std::setprecision(2);
    os << "[" << getName() << ", " << getCenter() << ", " << getArea() << "]";
}

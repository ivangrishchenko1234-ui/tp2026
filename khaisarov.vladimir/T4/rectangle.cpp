#include "rectangle.h"
#include <iostream>
#include <algorithm>

Rectangle::Rectangle(const Point& bl, const Point& tr) :
    bottomLeft(bl),
    topRight(tr)
{
}

double Rectangle::getArea() const
{
    double width = std::abs(topRight.x - bottomLeft.x);
    double height = std::abs(topRight.y - bottomLeft.y);
    return height * width;
}


Point Rectangle::getCenter() const
{
    double centerX = (bottomLeft.x + topRight.x) / 2.0;
    double centerY = (bottomLeft.y + topRight.y) / 2.0;
    return Point(centerX, centerY);
}

void Rectangle::scale(double factor)
{
    Point center = getCenter();
    bottomLeft.x = center.x - (center.x - bottomLeft.x) * factor;
    bottomLeft.y = center.y - (center.y - bottomLeft.y) * factor;
    topRight.x = center.x + (topRight.x - center.x) * factor;
    topRight.y = center.y + (topRight.y - center.y) * factor;
}

std::pair<Point, Point> Rectangle::Bounds() const
{
    return std::make_pair(bottomLeft, topRight);
}

std::string Rectangle::getName() const
{
    return "RECTANGLE";
}

void Rectangle::move(double dx, double dy)
{
    bottomLeft.x += dx;
    bottomLeft.y += dy;
    topRight.x += dx;
    topRight.y += dy;
}

void Rectangle::print(std::ostream& os) const
{
    os << std::fixed << std::setprecision(2);
    os << "[" << getName() << ", " << getCenter() << ", " << getArea() << "]";
}

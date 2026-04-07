#include <iostream>
#include <stdexcept>
#include "rectangle.h"


Rectangle::Rectangle(const Point& bl, const Point& tr)
{
    if (bl.x >= tr.x || bl.y >= tr.y)
    {
        throw std::invalid_argument("Uncorrect coordinates for rectangle\n");
    }

    bottomLeft = bl;
    topRight = tr;

}
double Rectangle::getArea() const
{
    double width = topRight.x - bottomLeft.x;
    double height = topRight.y - bottomLeft.y;
    return width * height;
}
Point Rectangle::getCenter() const
{
    double centerX = (topRight.x + bottomLeft.x) / 2.0;
    double centerY = (topRight.y + bottomLeft.y) / 2.0;
    return Point(centerX, centerY);
}
void Rectangle::move(double dx, double dy)
{
    bottomLeft.x += dx;
    bottomLeft.y += dy;
    topRight.x += dx;
    topRight.y += dy;
}

void Rectangle::scale(double factor)
{
    Point center = getCenter();
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;
    topRight.x = center.x + (topRight.x - center.x) * factor;
    topRight.y = center.y + (topRight.y - center.y) * factor;
}

std::string Rectangle::getName() const
{
    return "RECTANGLE";
}
std::pair<Point, Point> Rectangle::getFrame() const
{
    return { bottomLeft, topRight };
}

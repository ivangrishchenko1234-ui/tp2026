#include "Rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const Point& bl, const Point& tr) : bottomLeft(bl), topRight(tr)
{
    if (bottomLeft.x >= topRight.x || bottomLeft.y >= topRight.y)
    {
        throw std::invalid_argument("Invalid Rectangle coordinates");
    }
}

double Rectangle::getArea() const {
    double width = topRight.x - bottomLeft.x;
    double height = topRight.y - bottomLeft.y;
    return width * height;
}

Point Rectangle::getCenter() const {
    double centerX = (bottomLeft.x + topRight.x) / 2.0;
    double centerY = (bottomLeft.y + topRight.y) / 2.0;
    return Point(centerX, centerY);
}

void Rectangle::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;
    topRight.x += dx;
    topRight.y += dy;
}

void Rectangle::scale(double factor)
{
    if (factor <= 0.0)
    {
        throw std::invalid_argument("Scale factor must be positive");
    }

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

#include "rectangle.h"
#include <cmath>
#include <stdexcept>

Rectangle::Rectangle(const Point& corner1, const Point& corner2)
{
    if (corner1.x == corner2.x || corner1.y == corner2.y)
    {
        throw std::invalid_argument("Rectangle corners must not coincide on any axis");
    }

    corner1_.x = std::min(corner1.x, corner2.x);
    corner1_.y = std::min(corner1.y, corner2.y);
    corner2_.x = std::max(corner1.x, corner2.x);
    corner2_.y = std::max(corner1.y, corner2.y);
}

double Rectangle::getArea() const
{
    double side1 = corner2_.x - corner1_.x;
    double side2 = corner2_.y - corner1_.y;


    return side1 * side2;
}

Point Rectangle::getCenter() const
{
    Point center;
    center.x = (corner1_.x + corner2_.x) / 2;
    center.y = (corner1_.y + corner2_.y) / 2;

    return center;
}

void Rectangle::move(const Point& newCenter)
{
    Point center = getCenter();

    double dx = newCenter.x - center.x;
    double dy = newCenter.y - center.y;

    corner1_.x += dx;
    corner1_.y += dy;
    corner2_.x += dx;
    corner2_.y += dy;
}

void Rectangle::scale(double ratio)
{
    if(ratio <= 0)
    {
        throw std::invalid_argument("Ratio must be positive");
    }

    Point center = getCenter();

    corner1_.x = center.x + (corner1_.x - center.x) * ratio;
    corner1_.y = center.y + (corner1_.y - center.y) * ratio;

    corner2_.x = center.x + (corner2_.x - center.x) * ratio;
    corner2_.y = center.y + (corner2_.y - center.y) * ratio;
}

std::string Rectangle::getName() const
{
    return "Rectangle";
}

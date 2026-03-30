#include "square.h"
#include <stdexcept>

Square::Square(const Point& corner, double side)
{
    if (side <= 0.0)
    {
        throw std::invalid_argument("Side must be positive");
    }

    corner_ = corner;
    side_ = side;
}

double Square::getArea() const
{
    return side_ * side_;
}

Point Square::getCenter() const
{
    Point center;
    center.x = corner_.x + side_ / 2.0;
    center.y = corner_.y + side_ / 2.0;
    return center;
}

void Square::move(const Point& newCenter)
{
    corner_.x = newCenter.x - side_ / 2.0;
    corner_.y = newCenter.y - side_ / 2.0;
}

void Square::scale(double ratio)
{
    if (ratio <= 0.0)
    {
        throw std::invalid_argument("Ratio must be positive");
    }

    Point center = getCenter();
    side_ *= ratio;

    corner_.x = center.x - side_ / 2.0;
    corner_.y = center.y - side_ / 2.0;
}

std::string Square::getName() const
{
    return "SQUARE";
}

Bounds Square::getBounds() const
{
    return
    {
        corner_.x,
        corner_.y,
        corner_.x + side_,
        corner_.y + side_
    };
}

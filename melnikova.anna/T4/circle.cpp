#define _USE_MATH_DEFINES
#include <cmath>
#include "circle.h"

Circle::Circle(Point center, double radius) :
    center_(center)
{
    if (radius < 0) {
        throw std::invalid_argument("Circle: radius can't be less than zero");
    }
    radius_ = radius;
}

double Circle::getArea() const
{
    return (M_PI * radius_ * radius_);
}

Point Circle::getCenter() const
{
    return center_;
}

void Circle::move(double dx, double dy)
{
    center_ = { (center_.x + dx), (center_.y + dy) };
}

void Circle::scale(double coeff)
{
    if (coeff <= 0) {
        throw std::invalid_argument("Circle (scale): coefficient can't be less than zero");
    }
    radius_ *= coeff;
}

std::string Circle::getName() const
{
    return "CIRCLE";
}

RectanglePoints Circle::getBorderRectangle() const
{
    return {
        { center_.x - radius_, center_.y - radius_ },
        { center_.x + radius_, center_.y + radius_ }
    };
}

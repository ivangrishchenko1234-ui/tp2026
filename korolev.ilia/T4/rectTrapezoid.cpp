#include "rectTrapezoid.h"

RectTrapezoid::RectTrapezoid(double x, double y, double bottomBase,
    double topBase, double height) :
    bottomLeftX_(x),
    bottomLeftY_(y),
    bottomBase_(bottomBase),
    topBase_(topBase),
    height_(height)
{
}

double RectTrapezoid::getArea() const
{
    return (bottomBase_ + topBase_) / 2.0 * height_;
}

Point RectTrapezoid::getCenter() const
{
    double centerX = bottomLeftX_ + (bottomBase_ + topBase_) / 4.0;
    double centerY = bottomLeftY_ + height_ / 2.0;
    return Point(centerX, centerY);
}

void RectTrapezoid::move(double dx, double dy)
{
    bottomLeftX_ = bottomLeftX_ + dx;
    bottomLeftY_ = bottomLeftY_ + dy;
}

void RectTrapezoid::scale(double factor)
{
    Point center = getCenter();
    bottomBase_ = bottomBase_ * factor;
    topBase_ = topBase_ * factor;
    height_ = height_ * factor;
    bottomLeftX_ = center.x_ - (bottomBase_ + topBase_) / 4.0;
    bottomLeftY_ = center.y_ - height_ / 2.0;
}

const char* RectTrapezoid::getName() const
{
    return "RECT_TRAPEZOID";
}

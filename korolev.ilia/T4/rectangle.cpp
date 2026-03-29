#include "rectangle.h"

Rectangle::Rectangle(double leftX, double bottomY, double rightX, double topY) :
    leftX_(leftX),
    bottomY_(bottomY),
    rightX_(rightX),
    topY_(topY)
{
}

double Rectangle::getArea() const
{
    double width = rightX_ - leftX_;
    double height = topY_ - bottomY_;
    return width * height;
}

Point Rectangle::getCenter() const
{
    double centerX = (leftX_ + rightX_) / 2.0;
    double centerY = (bottomY_ + topY_) / 2.0;
    return Point(centerX, centerY);
}

void Rectangle::move(double dx, double dy)
{
    leftX_ = leftX_ + dx;
    rightX_ = rightX_ + dx;
    bottomY_ = bottomY_ + dy;
    topY_ = topY_ + dy;
}

void Rectangle::scale(double factor)
{
    Point center = getCenter();
    double width = rightX_ - leftX_;
    double height = topY_ - bottomY_;
    double newWidth = width * factor;
    double newHeight = height * factor;
    leftX_ = center.x_ - newWidth / 2.0;
    rightX_ = center.x_ + newWidth / 2.0;
    bottomY_ = center.y_ - newHeight / 2.0;
    topY_ = center.y_ + newHeight / 2.0;
}

const char* Rectangle::getName() const
{
    return "RECTANGLE";
}

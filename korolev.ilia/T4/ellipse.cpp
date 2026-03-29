#include "ellipse.h"

const double PI = 3.14159265358979323846;

Ellipse::Ellipse(double centerX, double centerY, double radiusX, double radiusY) :
    centerX_(centerX),
    centerY_(centerY),
    radiusX_(radiusX),
    radiusY_(radiusY)
{
}

double Ellipse::getArea() const
{
    return PI * radiusX_ * radiusY_;
}

Point Ellipse::getCenter() const
{
    return Point(centerX_, centerY_);
}

void Ellipse::move(double dx, double dy)
{
    centerX_ = centerX_ + dx;
    centerY_ = centerY_ + dy;
}

void Ellipse::scale(double factor)
{
    radiusX_ = radiusX_ * factor;
    radiusY_ = radiusY_ * factor;
}

const char* Ellipse::getName() const
{
    return "ELLIPSE";
}

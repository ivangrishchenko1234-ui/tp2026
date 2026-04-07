#include "ellipse.h"

Ellipse::Ellipse(const Point& cen, double rh, double rv) :
    centerE(cen),
    radiusHor(rh),
    radiusVer(rv)
{
}

double Ellipse::getArea() const
{
    return 3.1415 * radiusHor * radiusVer;
}

std::string Ellipse::getName() const
{
    return "ELLIPSE";
}


Point Ellipse::getCenter() const
{
    return centerE;
}

std::pair<Point, Point> Ellipse::Bounds() const
{
    double cx = getCenter().x;
    double cy = getCenter().y;
    Point bl = Point(cx - radiusHor, cy - radiusVer);
    Point tr = Point(cx + radiusHor, cy + radiusVer);
    return std::make_pair(bl, tr);
}

void Ellipse::move(double dx, double dy)
{
    centerE.x += dx;
    centerE.y += dy;
}

void Ellipse::scale(double factor)
{
    radiusVer *= factor;
    radiusHor *= factor;
}

void Ellipse::print(std::ostream& os) const
{
    os << std::fixed << std::setprecision(2);
    os << "[" << getName() << ", " << getCenter() << ", " << getArea() << "]";
}

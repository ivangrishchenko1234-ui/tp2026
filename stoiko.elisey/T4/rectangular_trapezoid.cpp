#include "rectangular_trapezoid.h"
#include <utility>

RectangularTrapezoid::RectangularTrapezoid(const Point& bl, double bb, double tb, double h)
    : bottomLeft(bl)
    , bottomBase(bb)
    , topBase(tb)
    , height(h)
{}

double RectangularTrapezoid::getArea() const {
    return (bottomBase + topBase) * height / 2.0;
}

double RectangularTrapezoid::getMidlineLength() const {
    return (bottomBase + topBase) / 2.0;
}

Point RectangularTrapezoid::getCenter() const {
    return Point(bottomLeft.x + getMidlineLength() / 2.0,
                    bottomLeft.y + height / 2.0);
}

void RectangularTrapezoid::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;
}

void RectangularTrapezoid::scale(double factor) {
    Point center = getCenter();
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;
    bottomBase *= factor;
    topBase *= factor;
    height *= factor;
}

std::string RectangularTrapezoid::getName() const {
    return "RECTANGULAR_TRAPEZOID";
}

std::pair<Point, Point> RectangularTrapezoid::getBounds() const {
    double maxBase = std::max(bottomBase, topBase);
    return std::make_pair(
        bottomLeft,
        Point(bottomLeft.x + maxBase, bottomLeft.y + height)
    );
}

void RectangularTrapezoid::print(std::ostream& stream) const {
    Point center = getCenter();
    stream << "[";
    stream << getName() << ", ";
    stream << "(" << center.x << ", " << center.y << ")" << ", ";
    stream << getArea() << "]";
}

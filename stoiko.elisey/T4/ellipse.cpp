#include "ellipse.h"

Ellipse::Ellipse(const Point& center, double horizontal_radius, double vertical_radius)
    : center(center)
    , horizontal_radius(horizontal_radius)
    , vertical_radius(vertical_radius)
{}

double Ellipse::getArea() const {
    return M_PI * horizontal_radius * vertical_radius;
}

Point Ellipse::getCenter() const {
    return center;
}

void Ellipse::move(double dx, double dy)  {
    center.x += dx;
    center.y += dy;
}

void Ellipse::scale(double factor)  {
    horizontal_radius *= factor;
    vertical_radius *= factor;
}

std::string Ellipse::getName() const {
    return "ELLIPSE";
}

std::pair<Point, Point> Ellipse::getBounds() const {
    return {
        Point(center.x - vertical_radius, center.y - horizontal_radius),
        Point(center.x + vertical_radius, center.y + horizontal_radius)
    };
}

void Ellipse::print(std::ostream& stream) const {
    Point center = getCenter();
    stream << "[";
    stream << getName() << ", ";
    stream << "(" << center.x << ", " << center.y << ")" << ", ";
    stream << getArea() << "]";
}

#include "trapezoid.h"
#include <algorithm>
#include <stdexcept>

IsoscelesTrapezoid::IsoscelesTrapezoid(Point p, double bb, double tb, double h) {
    if (bb <= 0 || tb <= 0 || h <= 0) {
        throw std::invalid_argument("Bases and height must be positive");
    }
    bl = p;
    bBase = bb;
    tBase = tb;
    height = h;
}

double IsoscelesTrapezoid::getArea() const {
    return (bBase + tBase) / 2.0 * height;
}

Point IsoscelesTrapezoid::getCenter() const {
    double cx = bl.x + (bBase + tBase) / 4.0;
    double cy = bl.y + height / 2.0;
    return { cx, cy };
}

void IsoscelesTrapezoid::move(double dx, double dy) {
    bl.x = bl.x + dx;
    bl.y = bl.y + dy;
}

void IsoscelesTrapezoid::scale(double factor) {
    Point c = getCenter();
    bBase = bBase * factor;
    tBase = tBase * factor;
    height = height * factor;
    bl.x = c.x - (bBase + tBase) / 4.0;
    bl.y = c.y - height / 2.0;
}

std::string IsoscelesTrapezoid::getName() const {
    return "TRAPEZOID";
}

void IsoscelesTrapezoid::getBoundingBox(Point& minP, Point& maxP) const {
    double cx = bl.x + bBase / 2.0;
    double x1 = bl.x;
    double x2 = bl.x + bBase;
    double x3 = cx - tBase / 2.0;
    double x4 = cx + tBase / 2.0;

    minP.x = x1;
    if (x2 < minP.x) minP.x = x2;
    if (x3 < minP.x) minP.x = x3;
    if (x4 < minP.x) minP.x = x4;

    maxP.x = x1;
    if (x2 > maxP.x) maxP.x = x2;
    if (x3 > maxP.x) maxP.x = x3;
    if (x4 > maxP.x) maxP.x = x4;

    minP.y = bl.y;
    maxP.y = bl.y + height;
}

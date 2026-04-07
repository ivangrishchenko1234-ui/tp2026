#include "Ring.h"
Ring::Ring(Point dot, double R_, double r_) : O(dot), R(R_), r(r_) {}
double Ring::getArea() { return PI * (R * R - r * r); }
Point Ring::getCenter() { return O; }
void Ring::move(double x_, double y_) { O.x += x_; O.y += y_; }
void Ring::scale(double k) { R *= k; r *= k; }
std::string Ring::getName() { return "RING"; }
double Ring::getX_min()
{
    return O.x - R;
}
double Ring::getX_max()
{
    return O.x + R;
}
double Ring::getY_min()
{
    return O.y - R;
}
double Ring::getY_max()
{
    return O.y + R;
}
void Ring::print()
{
    std::cout << "[" << getName() << ", (" << getCenter().x << ", " << getCenter().y << "), " << getArea() << "]\n";
}

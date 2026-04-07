#include "Rectangle.h"
Rectangle::Rectangle(Point A_, Point B_) : A(A_), B(B_) {}
double Rectangle::getArea() { return (B.x - A.x) * (B.y - A.y); }
Point Rectangle::getCenter() { return { (A.x + B.x) / 2, (A.y + B.y) / 2 }; }
void Rectangle::move(double x_, double y_)
{
    A.x += x_; A.y += y_;
    B.x += x_; B.y += y_;
}
void Rectangle::scale(double k)
{
    Point C = getCenter();
    A.x = C.x + (A.x - C.x) * k; A.y = C.y + (A.y - C.y) * k;
    B.x = C.x + (B.x - C.x) * k; B.y = C.y + (B.y - C.y) * k;
}
std::string Rectangle::getName() { return "RECTANGLE"; }
double Rectangle::getX_min()
{
    return A.x;
}
double Rectangle::getX_max()
{
    return B.x;
}
double Rectangle::getY_min()
{
    return A.y;
}
double Rectangle::getY_max()
{
    return B.y;
}
void Rectangle::print()
{
    std::cout << "[" << getName() << ", (" << getCenter().x << ", " << getCenter().y << "), " << getArea() << "]\n";
}

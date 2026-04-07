#include "Square.h"
Square::Square(Point dot, double len) : A(dot), length(len) {}
double Square::getArea() { return length * length; }
Point Square::getCenter() { return { A.x + length / 2, A.y + length / 2 }; }
void Square::move(double x_, double y_) { A.x += x_; A.y += y_; }
void Square::scale(double k)
{
    Point C = getCenter();
    A.x = C.x + (A.x - C.x) * k; A.y = C.y + (A.y - C.y) * k;
    length *= k;
}
std::string Square::getName() { return "SQUARE"; }
double Square::getX_min()
{
    return A.x;
}
double Square::getX_max()
{
    return A.x + length;
}
double Square::getY_min()
{
    return A.y;
}
double Square::getY_max()
{
    return A.y + length;
}
void Square::print()
{
    std::cout << "[" << getName() << ", (" << getCenter().x << ", " << getCenter().y << "), " << getArea() << "]\n";
}

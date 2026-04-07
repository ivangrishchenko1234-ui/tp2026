#include "trapezoid.h"
#include <stdexcept>
#include <algorithm>

Trapezoid::Trapezoid(const Point& bl, double a, double b, double h) :
    bl_(bl), a_(a), b_(b), h_(h) {
    if (a <= 0 || b <= 0 || h <= 0) throw std::invalid_argument("Sides must be > 0");
}

double Trapezoid::getArea() const { return (a_ + b_) / 2.0 * h_; }

Point Trapezoid::getCenter() const {
    return { bl_.x + (a_ + b_) / 4.0, bl_.y + h_ / 2.0 };
}

void Trapezoid::move(double dx, double dy) { bl_.x += dx; bl_.y += dy; }

void Trapezoid::move(const Point& nc) {
    Point current = getCenter();
    move(nc.x - current.x, nc.y - current.y);
}

void Trapezoid::scale(double k) {
    if (k <= 0) throw std::invalid_argument("Scale must be > 0");
    Point oldCenter = getCenter();
    a_ *= k; b_ *= k; h_ *= k;

    bl_.x = oldCenter.x - (a_ + b_) / 4.0;
    bl_.y = oldCenter.y - h_ / 2.0;
}

std::string Trapezoid::getName() const { return "TRAPEZOID"; }

double Trapezoid::getMaxX() const {
    double topOffset = (a_ - b_) / 2.0;
    return bl_.x + std::max(a_, b_ + topOffset);
}

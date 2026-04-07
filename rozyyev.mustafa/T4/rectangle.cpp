#include "rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const Point& bl, const Point& tr) : bl_(bl), tr_(tr) {
    if (bl.x >= tr.x || bl.y >= tr.y) {
        throw std::invalid_argument("Invalid rectangle points");
    }
}

double Rectangle::getArea() const {
    return (tr_.x - bl_.x) * (tr_.y - bl_.y);
}

Point Rectangle::getCenter() const {
    return { (bl_.x + tr_.x) / 2.0, (bl_.y + tr_.y) / 2.0 };
}

void Rectangle::move(double dx, double dy) {
    bl_.x += dx; bl_.y += dy;
    tr_.x += dx; tr_.y += dy;
}

void Rectangle::move(const Point& newCenter) {
    Point current = getCenter();
    move(newCenter.x - current.x, newCenter.y - current.y);
}

void Rectangle::scale(double k) {
    if (k <= 0) throw std::invalid_argument("Scale k must be positive");
    Point c = getCenter();
    bl_.x = c.x + (bl_.x - c.x) * k;
    bl_.y = c.y + (bl_.y - c.y) * k;
    tr_.x = c.x + (tr_.x - c.x) * k;
    tr_.y = c.y + (tr_.y - c.y) * k;
}

std::string Rectangle::getName() const { return "RECTANGLE"; }

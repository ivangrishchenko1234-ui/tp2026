#include "composite_shape.h"
#include <algorithm>
#include <limits>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (shape) {
        shapes_.push_back(std::move(shape));
    }
}

double CompositeShape::getArea() const {
    double total = 0.0;
    for (const auto& s : shapes_) {
        total += s->getArea();
    }
    return total;
}

std::pair<Point, Point> CompositeShape::getBounds() const {
    if (shapes_.empty()) {
        return {Point(0, 0), Point(0, 0)};
    }
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = -std::numeric_limits<double>::max();
    double maxY = -std::numeric_limits<double>::max();
    for (const auto& s : shapes_) {
        Point c = s->getCenter();
        minX = std::min(minX, c.x);
        minY = std::min(minY, c.y);
        maxX = std::max(maxX, c.x);
        maxY = std::max(maxY, c.y);
    }
    return {Point(minX, minY), Point(maxX, maxY)};
}

Point CompositeShape::getCenter() const {
    auto bounds = getBounds();
    double cx = (bounds.first.x + bounds.second.x) / 2.0;
    double cy = (bounds.first.y + bounds.second.y) / 2.0;
    return Point(cx, cy);
}

void CompositeShape::move(double dx, double dy) {
    for (auto& s : shapes_) {
        s->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (shapes_.empty()) return;
    Point center = getCenter();
    for (auto& s : shapes_) {
        Point c = s->getCenter();
        double dx = c.x - center.x;
        double dy = c.y - center.y;
        Point newC(center.x + dx * factor, center.y + dy * factor);
        s->move(newC.x - c.x, newC.y - c.y);
        s->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

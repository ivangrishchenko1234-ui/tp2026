#include "Composite_shape.h"
#include <iostream>
#include <algorithm>
void CompositeShape::addShape(std::shared_ptr<Shape> shape) {
    shapes_.push_back(shape);
}
double CompositeShape::getArea() const {
    double total = 0;
    for (auto& s : shapes_) total += s->getArea();
    return total;
}
Point CompositeShape::getCenter() const {
    if (shapes_.empty()) {
        return {0,0};
    }
    double minX = shapes_[0]->getCenter().x;
    double maxX = minX;
    double minY = shapes_[0]->getCenter().y;
    double maxY = minY;
    for (const auto& s : shapes_) {
        Point c = s->getCenter();
        if (c.x < minX) {
            minX = c.x;
        }
        if (c.x > maxX) {
            maxX = c.x;
        }
        if (c.y < minY) {
            minY = c.y;
        }
        if (c.y > maxY) {
            maxY = c.y;
        }
    }
    return {(minX + maxX) / 2.0, (minY + maxY) / 2.0};
}
void CompositeShape::move(double dx, double dy) {
    for (auto& s : shapes_) s->move(dx, dy);
}
void CompositeShape::scale(double factor) {
    Point baseCenter = getCenter();
    for (auto& s : shapes_) {
        Point c = s->getCenter();
        double dx = (c.x - baseCenter.x) * (factor - 1);
        double dy = (c.y - baseCenter.y) * (factor - 1);
        s->move(dx, dy);
        s->scale(factor);
    }
}
std::string CompositeShape::getName() const {
    return "COMPOSITE";
}
const std::vector<std::shared_ptr<Shape>>& CompositeShape::getShapes() const {
    return shapes_;
}


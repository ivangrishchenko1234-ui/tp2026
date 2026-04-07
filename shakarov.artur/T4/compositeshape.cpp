#include "compositeshape.h"
#include <algorithm>
#include <limits>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double total = 0.0;
    for (const auto& s : shapes_) {
        total += s->getArea();
    }
    return total;
}

Point CompositeShape::getCenter() const {
    if (shapes_.empty()) {
        return Point(0, 0);
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

    return Point((minX + maxX) / 2.0, (minY + maxY) / 2.0);
}

void CompositeShape::move(double dx, double dy) {
    for (auto& s : shapes_) {
        s->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point compCenter = getCenter();

    for (auto& s : shapes_) {
        Point shapeCenter = s->getCenter();

        double dx = (shapeCenter.x - compCenter.x) * (factor - 1.0);
        double dy = (shapeCenter.y - compCenter.y) * (factor - 1.0);
        s->move(dx, dy);
        s->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const {
    return shapes_;
}

#include "composite_shape.h"
#include <algorithm>
#include <limits>
#include <cmath>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double total = 0.0;
    for (const auto& shape : shapes_) {
        total += shape->getArea();
    }
    return total;
}

Point CompositeShape::getCenter() const {
    if (shapes_.empty()) {
        return { 0.0, 0.0 };
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto& shape : shapes_) {
        Point center = shape->getCenter();
        minX = std::min(minX, center.x);
        minY = std::min(minY, center.y);
        maxX = std::max(maxX, center.x);
        maxY = std::max(maxY, center.y);
    }

    Point center;
    center.x = (minX + maxX) / 2.0;
    center.y = (minY + maxY) / 2.0;
    return center;
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes_) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point commonCenter = getCenter();
    for (auto& shape : shapes_) {
        Point shapeCenter = shape->getCenter();
        double dx = shapeCenter.x - commonCenter.x;
        double dy = shapeCenter.y - commonCenter.y;
        shape->move(dx * (factor - 1.0), dy * (factor - 1.0));
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const {
    return shapes_;
}

#include "composite_shape.h"
#include <stdexcept>
#include <algorithm>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (shape == nullptr) {
        throw std::invalid_argument("Cannot add null shape");
    }
    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double totalArea = 0.0;
    for (const auto &shape : shapes_) {
        totalArea += shape->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const {
    if (shapes_.empty()) {
        throw std::logic_error("Composite shape is empty");
    }
    Point firstC = shapes_[0]->getCenter();
    double minX = firstC.x, maxX = firstC.x, minY = firstC.y, maxY = firstC.y;
    for (const auto &s : shapes_) {
        Point c = s->getCenter();
        minX = std::min(minX, c.x);
        maxX = std::max(maxX, c.x);
        minY = std::min(minY, c.y);
        maxY = std::max(maxY, c.y);
    }
    return {(minX + maxX) / 2.0, (minY + maxY) / 2.0};
}

void CompositeShape::move(double dx, double dy) {
    for (const auto &s : shapes_) {
        s->move(dx, dy);
    }
}

void CompositeShape::move(const Point &newCenter) {
    Point currentCenter = getCenter();
    move(newCenter.x - currentCenter.x, newCenter.y - currentCenter.y);
}

void CompositeShape::scale(double factor) {
    if (factor <= 0.0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    Point commonCenter = getCenter();
    for (const auto &s : shapes_) {
        Point sCenter = s->getCenter();
        double dx = (sCenter.x - commonCenter.x) * factor;
        double dy = (sCenter.y - commonCenter.y) * factor;
        s->move({commonCenter.x + dx, commonCenter.y + dy});
        s->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

size_t CompositeShape::getSize() const {
    return shapes_.size();
}

const Shape* CompositeShape::getShape(size_t index) const {
    if (index >= shapes_.size()) {
        throw std::out_of_range("Index out of range");
    }
    return shapes_[index].get();
}

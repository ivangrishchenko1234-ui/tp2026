#include "CompositeShape.h"
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <cmath>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes_.push_back(std::move(shape));
}

Shape* CompositeShape::getShape(size_t index) const {
    if (index >= shapes_.size()) {
        throw std::out_of_range("Index out of range");
    }
    return shapes_[index].get();
}

void CompositeShape::getBoundingBox(Point& min, Point& max) const {
    if (isEmpty()) {
        min = Point(0, 0);
        max = Point(0, 0);
        return;
    }

    min.x = std::numeric_limits<double>::max();
    min.y = std::numeric_limits<double>::max();
    max.x = -std::numeric_limits<double>::max();
    max.y = -std::numeric_limits<double>::max();

    // Iterate through all shapes and find their centers
    for (const auto& shape : shapes_) {
        Point center = shape->getCenter();
        min.x = std::min(min.x, center.x);
        min.y = std::min(min.y, center.y);
        max.x = std::max(max.x, center.x);
        max.y = std::max(max.y, center.y);
    }
}

double CompositeShape::getArea() const {
    double total = 0;
    for (const auto& shape : shapes_) {
        total += shape->getArea();
    }
    return total;
}

Point CompositeShape::getCenter() const {
    // Center of bounding box based on shape centers
    Point min, max;
    getBoundingBox(min, max);
    return Point((min.x + max.x) / 2, (min.y + max.y) / 2);
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes_) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (isEmpty()) return;

    // Step 1: get composite shape center
    Point compositeCenter = getCenter();

    // Step 2: process each shape
    for (auto& shape : shapes_) {
        // Step 2.1: get current shape center
        Point shapeCenter = shape->getCenter();

        // Step 2.2: calculate vector from composite center to shape center
        double dx = shapeCenter.x - compositeCenter.x;
        double dy = shapeCenter.y - compositeCenter.y;

        // Step 2.3: scale the vector
        double newDx = dx * factor;
        double newDy = dy * factor;

        // Step 2.4: calculate new shape center position
        Point newShapeCenter(
            compositeCenter.x + newDx,
            compositeCenter.y + newDy
        );

        // Step 2.5: move shape to new position
        double moveX = newShapeCenter.x - shapeCenter.x;
        double moveY = newShapeCenter.y - shapeCenter.y;
        shape->move(moveX, moveY);

        // Step 2.6: scale the shape itself
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}
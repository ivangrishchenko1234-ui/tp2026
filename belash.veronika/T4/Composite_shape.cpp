#include "Composite_shape.hpp"
#include <algorithm>

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


Shape::BoundingBox CompositeShape::getBoundingBox() const {
    if (shapes_.empty()) {
        return { Point(0, 0), Point(0, 0) };
    }

    auto bb = shapes_[0]->getBoundingBox();
    double minX = bb.min.x, maxX = bb.max.x;
    double minY = bb.min.y, maxY = bb.max.y;

    for (size_t i = 1; i < shapes_.size(); ++i) {
        auto current = shapes_[i]->getBoundingBox();
        minX = std::min(minX, current.min.x);
        maxX = std::max(maxX, current.max.x);
        minY = std::min(minY, current.min.y);
        maxY = std::max(maxY, current.max.y);
    }

    return { Point(minX, minY), Point(maxX, maxY) };
}

Point CompositeShape::getCenter() const {
    auto bb = getBoundingBox();
    return Point((bb.min.x + bb.max.x) / 2.0, (bb.min.y + bb.max.y) / 2.0);
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes_) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point compositeCenter = getCenter();

    for (auto& shape : shapes_) {
        Point shapeCenter = shape->getCenter();

        double dx = shapeCenter.x - compositeCenter.x;
        double dy = shapeCenter.y - compositeCenter.y;

        double newDx = dx * factor;
        double newDy = dy * factor;

        Point newShapeCenter(
            compositeCenter.x + newDx,
            compositeCenter.y + newDy
        );

        double moveX = newShapeCenter.x - shapeCenter.x;
        double moveY = newShapeCenter.y - shapeCenter.y;

        shape->move(moveX, moveY);
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const {
    return shapes_;
}

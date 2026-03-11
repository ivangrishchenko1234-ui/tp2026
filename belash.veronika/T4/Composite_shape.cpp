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

Point CompositeShape::getCenter() const {
    if (shapes_.empty()) {
        return Point(0, 0);
    }

    double minX = shapes_[0]->getCenter().x;
    double maxX = shapes_[0]->getCenter().x;
    double minY = shapes_[0]->getCenter().y;
    double maxY = shapes_[0]->getCenter().y;

    for (const auto& shape : shapes_) {
        Point center = shape->getCenter();
        minX = std::min(minX, center.x);
        maxX = std::max(maxX, center.x);
        minY = std::min(minY, center.y);
        maxY = std::max(maxY, center.y);
    }

    return Point((minX + maxX) / 2.0, (minY + maxY) / 2.0);
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

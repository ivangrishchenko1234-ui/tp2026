#include "composite-shape.h"

void CompositeShape::add(std::shared_ptr<Shape> shape) {
    if (shape == nullptr) {
        throw std::invalid_argument("Shape pointer cannot be null");
    }
    shapes_.push_back(shape);
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

    Point firstCenter = shapes_[0]->getCenter();
    double minX = firstCenter.x;
    double maxX = firstCenter.x;
    double minY = firstCenter.y;
    double maxY = firstCenter.y;

    for (const auto &shape : shapes_) {
        Point c = shape->getCenter();

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
    for (auto &shape : shapes_) {
        shape->move(dx, dy);
    }
}

void CompositeShape::move(const Point &newCenter) {
    Point currentCenter = getCenter();
    move(newCenter.x - currentCenter.x, newCenter.y - currentCenter.y);
}

void CompositeShape::scale(double coefficient) {
    if (coefficient <= 0.0) {
        throw std::invalid_argument("Scale coefficient must be positive");
    }
    Point commonCenter = getCenter();
    for (auto &shape : shapes_) {
        Point shapeCenter = shape->getCenter();

        double dx = (shapeCenter.x - commonCenter.x) * coefficient;
        double dy = (shapeCenter.y - commonCenter.y) * coefficient;

        shape->move({commonCenter.x + dx, commonCenter.y + dy});
        shape->scale(coefficient);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE SHAPE";
}
    
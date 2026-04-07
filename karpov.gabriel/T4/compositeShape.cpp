#include "compositeShape.h"
#include <string>
#include <algorithm>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double totalSum = 0.0;
    for (const auto& shape : shapes_) {
        totalSum += shape->getArea();
    }
    return totalSum;
}

Point CompositeShape::getCenter() const {
    if (shapes_.empty())
        return Point(0, 0);
    double minX = shapes_[0]->getMinX();
    double minY = shapes_[0]->getMinY();
    double maxX = shapes_[0]->getMaxX();
    double maxY = shapes_[0]->getMaxY();
    for (const auto& shape : shapes_) {
        if (shape->getMinX() < minX) minX = shape->getMinX();
        if (shape->getMinY() < minY) minY = shape->getMinY();
        if (shape->getMaxX() > maxX) maxX = shape->getMaxX();
        if (shape->getMaxY() > maxY) maxY = shape->getMaxY();
    }
    double centerX = (minX + maxX) / 2.0;
    double centerY = (minY + maxY) / 2.0;
    return Point(centerX, centerY);
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes_) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (shapes_.empty())
        return;
    Point center = getCenter();
    for (auto& shape : shapes_) {
        Point oldCenter = shape->getCenter();
        double dx = oldCenter.x - center.x;
        double dy = oldCenter.y - center.y;
        double newDx = dx * factor;
        double newDy = dy * factor;
        shape->scale(factor);
        shape->move(newDx - dx, newDy - dy);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

double CompositeShape::getMinX() const {
    if (shapes_.empty())
        return 0;
    double minX = shapes_[0]->getMinX();
    for (const auto& shape : shapes_) {
        if (shape->getMinX() < minX) minX = shape->getMinX();
    }
    return minX;
}

double CompositeShape::getMinY() const {
    if (shapes_.empty())
        return 0;
    double minY = shapes_[0]->getMinY();
    for (const auto& shape : shapes_) {
        if (shape->getMinY() < minY) minY = shape->getMinY();
    }
    return minY;
}

double CompositeShape::getMaxX() const {
    if (shapes_.empty())
        return 0;
    double maxX = shapes_[0]->getMaxX();
    for (const auto& shape : shapes_) {
        if (shape->getMaxX() > maxX) maxX = shape->getMaxX();
    }
    return maxX;
}

double CompositeShape::getMaxY() const {
    if (shapes_.empty())
        return 0;
    double maxY = shapes_[0]->getMaxY();
    for (const auto& shape : shapes_) {
        if (shape->getMaxY() > maxY) maxY = shape->getMaxY();
    }
    return maxY;
}

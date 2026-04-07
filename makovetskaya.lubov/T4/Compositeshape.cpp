#include "Compositeshape.h"
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <cmath>

void CompositeShape::addShape(std::shared_ptr<Shape> shape) {
    if (shape) {
        shapes.push_back(shape);
    }
}

void CompositeShape::removeShape(std::shared_ptr<Shape> shape) {
    for (auto it = shapes.begin(); it != shapes.end(); ++it) {
        if (*it == shape) {
            shapes.erase(it);
            break;
        }
    }
}

void CompositeShape::getBoundingBox(double& minX, double& minY, double& maxX, double& maxY) const {
    if (shapes.empty()) {
        minX = minY = maxX = maxY = 0;
        return;
    }

    minX = std::numeric_limits<double>::max();
    minY = std::numeric_limits<double>::max();
    maxX = std::numeric_limits<double>::lowest();
    maxY = std::numeric_limits<double>::lowest();

    for (const auto& shape : shapes) {
        Point center = shape->getCenter();
        double area = shape->getArea();
        double halfSize = std::sqrt(area) / 2.0;

        minX = std::min(minX, center.x - halfSize);
        minY = std::min(minY, center.y - halfSize);
        maxX = std::max(maxX, center.x + halfSize);
        maxY = std::max(maxY, center.y + halfSize);
    }
}

double CompositeShape::getArea() const {
    double totalArea = 0;
    for (const auto& shape : shapes) {
        totalArea += shape->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const {
    if (shapes.empty()) return Point(0, 0);

    double totalArea = getArea();
    double weightedX = 0, weightedY = 0;

    for (const auto& shape : shapes) {
        Point center = shape->getCenter();
        double area = shape->getArea();
        weightedX += center.x * area;
        weightedY += center.y * area;
    }

    return Point(weightedX / totalArea, weightedY / totalArea);
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (shapes.empty()) return;

    Point compositeCenter = getCenter();

    for (auto& shape : shapes) {
        Point shapeCenter = shape->getCenter();

        double dx = shapeCenter.x - compositeCenter.x;
        double dy = shapeCenter.y - compositeCenter.y;

        double newDx = dx * factor;
        double newDy = dy * factor;

        shape->move(newDx - dx, newDy - dy);

        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

size_t CompositeShape::getCount() const {
    return shapes.size();
}

const std::vector<std::shared_ptr<Shape>>& CompositeShape::getShapes() const {
    return shapes;
}

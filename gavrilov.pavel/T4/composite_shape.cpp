#include "composite_shape.h"
#include <algorithm>
#include <cstdio>
#include <stdexcept>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (shape == nullptr) {
        throw std::invalid_argument("Cannot add nullptr shape");
    }
    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double total = 0;
    for (const auto& shape : shapes_) {
        total += shape->getArea();
    }
    return total;
}

Point CompositeShape::getCenter() const {
    if (shapes_.empty()) return Point(0, 0);

    double totalArea = getArea();
    if (totalArea == 0) return Point(0, 0);

    double weightedX = 0, weightedY = 0;
    for (const auto& shape : shapes_) {
        double area = shape->getArea();
        Point center = shape->getCenter();
        weightedX += center.x * area;
        weightedY += center.y * area;
    }

    return Point(weightedX / totalArea, weightedY / totalArea);
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes_) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }

    Point center = getCenter();

    for (auto& shape : shapes_) {
        Point shapeCenter = shape->getCenter();

        Point newCenter(
            center.x + (shapeCenter.x - center.x) * factor,
            center.y + (shapeCenter.y - center.y) * factor
        );

        shape->move(newCenter.x - shapeCenter.x, newCenter.y - shapeCenter.y);
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

void CompositeShape::print() const {
    printf("[%s, (%.2f, %.2f), %.2f:\n",
        getName().c_str(),
        getCenter().x, getCenter().y,
        getArea());

    for (size_t i = 0; i < shapes_.size(); ++i) {
        printf("  ");
        shapes_[i]->print();
        if (i < shapes_.size() - 1) {
            printf(",\n");
        }
        else {
            printf("\n");
        }
    }
    printf("]");
}

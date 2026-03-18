#include "Composite_Shape.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (!shape)
        throw std::invalid_argument("Null shape");

    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double totalArea = 0;
    for (size_t i = 0; i < shapes_.size(); i++) {
        totalArea += shapes_[i]->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const {
    if (shapes_.empty()) {
        return Point(0, 0);
    }

    double sumX = 0;
    double sumY = 0;

    for (size_t i = 1; i < shapes_.size(); i++) {
        Point center = shapes_[i]->getCenter();

        sumX += center.x_;
        sumY += center.y_;
    }
    double centerX = sumX / shapes_.size();
    double centerY = sumY / shapes_.size();

    return Point(centerX, centerY);
}

void CompositeShape::move(double dx, double dy) {
    for (size_t i = 0; i < shapes_.size(); i++) {
        shapes_[i]->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (factor <= 0)
        throw std::invalid_argument("Scale factor must be positive");

    Point center = getCenter();

    for (size_t i = 0; i < shapes_.size(); i++) {
        Point shapeCenter = shapes_[i]->getCenter();
        double newCenterX = center.x_ + (shapeCenter.x_ - center.x_) * factor;
        double newCenterY = center.y_ + (shapeCenter.y_ - center.y_) * factor;

        double dx = newCenterX - shapeCenter.x_;
        double dy = newCenterY - shapeCenter.y_;

        shapes_[i]->move(dx, dy);
        shapes_[i]->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

void CompositeShape::print() const {
    Point center = getCenter();
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "[" << getName()
            << ", (" << center.x_ << ", " << center.y_ << "), "
            << getArea() << ":\n";

    for (size_t i = 0; i < shapes_.size(); i++) {
        Point shapeCenter = shapes_[i]->getCenter();
        std::cout << "  "
                << shapes_[i]->getName()
                << ", (" << shapeCenter.x_ << ", " << shapeCenter.y_ << "), "
                << shapes_[i]->getArea() << ",\n";
    }
    std::cout << "]\n\n";
}

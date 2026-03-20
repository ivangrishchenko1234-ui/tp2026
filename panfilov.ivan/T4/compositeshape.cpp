#include "compositeshape.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double area = 0;
    for (const auto& shape : shapes) {
        area += shape->getArea();
    }
    return area;
}

Point CompositeShape::getCenter() const {
    if (shapes.empty()) {
        return Point(0, 0);
    }
    double sumX = 0, sumY = 0;
    for (const auto& shape : shapes) {
        Point center = shape->getCenter();
        sumX += center.x_;
        sumY += center.y_;
    }
    return Point(sumX / shapes.size(), sumY / shapes.size());
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (shapes.empty()) {
        return;
    }
    Point compositeCenter = getCenter();
    for (auto& shape : shapes) {
        Point shapeCenter = shape->getCenter();
        double dx = shapeCenter.x_ - compositeCenter.x_;
        double dy = shapeCenter.y_ - compositeCenter.y_;
        double newDx = dx * factor;
        double newDy = dy * factor;
        Point newShapeCenter(compositeCenter.x_ + newDx, compositeCenter.y_ + newDy);
        shape->move(newShapeCenter.x_ - shapeCenter.x_, newShapeCenter.y_ - shapeCenter.y_);
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

void CompositeShape::print() const {
    std::cout << "[" << getName() << ", (" << std::fixed << std::setprecision(2) << getCenter().x_
        << ", " << getCenter().y_ << "), " << getArea() << ":\n";
    for (const auto& shape : shapes) {
        std::cout << "  ";
        shape->print();
    }
    std::cout << "]\n";
}

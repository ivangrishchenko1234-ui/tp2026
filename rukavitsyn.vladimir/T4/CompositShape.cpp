#include "CompositShape.h"
#include <algorithm>
#include <cmath>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (shape) {
        shapes.push_back(std::move(shape));
    }
}

double CompositeShape::getArea() const {
    double area = 0.0;
    for (const auto& shape : shapes) {
        area += shape->getArea();
    }
    return area;
}

Point CompositeShape::getCenter() const {
    if (shapes.empty()) {
        return Point(0, 0);
    }

    auto rect = circumscribedRectangle();
    return Point((rect.first.x_ + rect.second.x_) / 2.0,
        (rect.first.y_ + rect.second.y_) / 2.0);
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (factor <= 0.0) {
        return;
    }

    Point compositeCenter = getCenter();

    for (auto& shape : shapes) {
        Point shapeCenter = shape->getCenter();
        double newX = compositeCenter.x_ + (shapeCenter.x_ - compositeCenter.x_) * factor;
        double newY = compositeCenter.y_ + (shapeCenter.y_ - compositeCenter.y_) * factor;
        shape->move(newX - shapeCenter.x_, newY - shapeCenter.y_);
        shape->scale(factor);
    }
}

std::pair<Point, Point> CompositeShape::circumscribedRectangle() const {
    if (shapes.empty()) {
        return { Point(0, 0), Point(0, 0) };
    }

    auto firstRect = shapes[0]->circumscribedRectangle();
    double minX = firstRect.first.x_;
    double minY = firstRect.first.y_;
    double maxX = firstRect.second.x_;
    double maxY = firstRect.second.y_;

    for (const auto& shape : shapes) {
        auto rect = shape->circumscribedRectangle();
        minX = std::min(minX, rect.first.x_);
        minY = std::min(minY, rect.first.y_);
        maxX = std::max(maxX, rect.second.x_);
        maxY = std::max(maxY, rect.second.y_);
    }

    return { Point(minX, minY), Point(maxX, maxY) };
}

std::string CompositeShape::getName() const {
    return "CompositeShape";
}

void CompositeShape::print(std::ostream& stream) const {
    stream << "[ " << getName() << ": center = (" << getCenter().x_
        << ", " << getCenter().y_ << "), Area = " << getArea() << ":\n";
    for (const auto& shape : shapes) {
        shape->print(stream);
    }
    stream << "]\n";
}

#include "composite_shape.h"

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double total = 0.0;
    for (const auto& s : shapes) {
        total += s->getArea();
    }
    return total;
}

Point CompositeShape::getCenter() const {
    if (shapes.empty()) {
        return Point(0, 0);
    }
    double sumX = 0.0;
    double sumY = 0.0;

    for (const auto& s : shapes) {
        Point c = s->getCenter();
        sumX += c.x;
        sumY += c.y;
    }
    return Point(sumX / shapes.size(), sumY / shapes.size());
}

void CompositeShape::move(double dx, double dy) {
    for (auto& s : shapes) {
        s->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point compCenter = getCenter();
    for (auto& s : shapes) {
        Point shapeCenter = s->getCenter();

        double dx = shapeCenter.x - compCenter.x;
        double dy = shapeCenter.y - compCenter.y;

        double newDx = dx * factor;
        double newDy = dy * factor;

        Point newShapeCenter(compCenter.x + newDx, compCenter.y + newDy);

        s->move(newShapeCenter.x - shapeCenter.x, newShapeCenter.y - shapeCenter.y);
        s->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

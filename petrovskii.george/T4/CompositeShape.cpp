#include <iostream>
#include <stdexcept>
#include "CompositeShape.h"

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (shape == nullptr) {
        throw std::invalid_argument("CompositeShape: cannot add null shape");
    }
    shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double total = 0.0;
    for (size_t i = 0; i < shapes.size(); ++i) {
        total += shapes[i]->getArea();
    }
    return total;
}

Point CompositeShape::getCenter() const {
    return calculateCenter();
}

Point CompositeShape::calculateCenter() const {
    if (shapes.empty()) {
        return Point(0, 0);
    }


    double minX = shapes[0]->getCenter().x;
    double minY = shapes[0]->getCenter().y;
    double maxX = shapes[0]->getCenter().x;
    double maxY = shapes[0]->getCenter().y;


    for (size_t i = 1; i < shapes.size(); ++i) {
        Point center = shapes[i]->getCenter();

        if (center.x < minX) {
            minX = center.x;
        }
        if (center.y < minY) {
            minY = center.y;
        }
        if (center.x > maxX) {
            maxX = center.x;
        }
        if (center.y > maxY) {
            maxY = center.y;
        }
    }

    return Point((minX + maxX) / 2.0, (minY + maxY) / 2.0);
}

void CompositeShape::move(double dx, double dy) {
    for (size_t i = 0; i < shapes.size(); ++i) {
        shapes[i]->move(dx, dy);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

void CompositeShape::scale(double fact) {
    if (fact <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }

    Point compositeCenter = getCenter();

    for (size_t i = 0; i < shapes.size(); ++i) {

        Point shapeCenter = shapes[i]->getCenter();

        double dx = shapeCenter.x - compositeCenter.x;
        double dy = shapeCenter.y - compositeCenter.y;

        double newDx = dx * fact;
        double newDy = dy * fact;

        Point newShapeCenter(compositeCenter.x + newDx, compositeCenter.y + newDy);

        double moveX = newShapeCenter.x - shapeCenter.x;
        double moveY = newShapeCenter.y - shapeCenter.y;
        shapes[i]->move(moveX, moveY);

        shapes[i]->scale(fact);
    }
}

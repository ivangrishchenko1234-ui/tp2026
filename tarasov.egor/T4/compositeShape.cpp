#include <string>
#include "point.h"
#include "compositeShape.h"
#include "rectangle.h"
#include "circle.h"
#include "rhomb.h"
#include <algorithm>

double CompositeShape::getArea() const {
    double totalArea = 0.0;
    for (size_t i = 0; i < shapes_.size(); ++i) {
        totalArea += shapes_[i]->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const {
    if (shapes_.empty()) {
        return Point(0, 0);
    }

    double minX, minY, maxX, maxY;
    getBoundingBox(minX, minY, maxX, maxY);

    return Point((minX + maxX) / 2, (minY + maxY) / 2);
}

void CompositeShape::move(double a, double b) {
    for (size_t i = 0; i < shapes_.size(); ++i) {
        shapes_[i]->move(a, b);
    }
}

void CompositeShape::scale(double c) {
    if (shapes_.empty() || c <= 0) {
        return;
    }

    Point compositeCenter = getCenter();

    for (size_t i = 0; i < shapes_.size(); ++i) {
        Point shapeCenter = shapes_[i]->getCenter();

        double newX = compositeCenter.x + (shapeCenter.x - compositeCenter.x) * c;
        double newY = compositeCenter.y + (shapeCenter.y - compositeCenter.y) * c;

        shapes_[i]->move(newX - shapeCenter.x, newY - shapeCenter.y);
        shapes_[i]->scale(c);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (shape) {
        shapes_.push_back(std::move(shape));
    }
}

void CompositeShape::getBoundingBox(double& minX, double& minY,
                                     double& maxX, double& maxY) const {
    if (shapes_.empty()) {
        minX = minY = maxX = maxY = 0;
        return;
    }
    double tempMinX, tempMinY, tempMaxX, tempMaxY;
    shapes_[0]->getBoundingBox(tempMinX, tempMinY, tempMaxX, tempMaxY);

    minX = tempMinX;
    minY = tempMinY;
    maxX = tempMaxX;
    maxY = tempMaxY;

    for (size_t i = 1; i < shapes_.size(); ++i) {
        shapes_[i]->getBoundingBox(tempMinX, tempMinY, tempMaxX, tempMaxY);

        minX = std::min(minX, tempMinX);
        minY = std::min(minY, tempMinY);
        maxX = std::max(maxX, tempMaxX);
        maxY = std::max(maxY, tempMaxY);
    }
}

std::ostream& operator<<(std::ostream& os, const CompositeShape& composite) {
    os << "[" << composite.getName() << ", "
       << composite.getCenter() << ", "
       << composite.getArea() << ":\n";

    for (size_t i = 0; i < composite.shapes_.size(); ++i) {
        const Shape* shape = composite.shapes_[i].get();
        os << "    " << shape->getName() << ", "
           << shape->getCenter() << ", "
           << shape->getArea();

        if (i < composite.shapes_.size() - 1) {
            os << ",\n";
        } else {
            os << "\n";
        }
    }

    os << "]";
    return os;
}

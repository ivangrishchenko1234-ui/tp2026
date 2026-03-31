#include <string>
#include "point.h"
#include "compositeShape.h"
#include "rectangle.h"
#include "circle.h"
#include "rhomb.h"
#include <iomanip>
#include <algorithm>
#include <limits>

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
    getBounds(minX, minY, maxX, maxY);

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

void CompositeShape::getBounds(double& minX, double& minY, double& maxX, double& maxY) const {
    if (shapes_.empty()) {
        minX = minY = maxX = maxY = 0;
        return;
    }

    minX = std::numeric_limits<double>::max();
    minY = std::numeric_limits<double>::max();
    maxX = std::numeric_limits<double>::lowest();
    maxY = std::numeric_limits<double>::lowest();

    for (size_t i = 0; i < shapes_.size(); ++i) {
        std::string shapeName = shapes_[i]->getName();

        if (shapeName == "RECTANGLE") {
            Rectangle* rect = static_cast<Rectangle*>(shapes_[i].get());
            Point l = rect->getLeftBottom();
            Point r = rect->getRightTop();

            minX = std::min(minX, std::min(l.x, r.x));
            minY = std::min(minY, std::min(l.y, r.y));
            maxX = std::max(maxX, std::max(l.x, r.x));
            maxY = std::max(maxY, std::max(l.y, r.y));
        }
        else if (shapeName == "CIRCLE") {
            Circle* circle = static_cast<Circle*>(shapes_[i].get());
            Point center = circle->getCenter();
            double radius = circle->getRadius();

            minX = std::min(minX, center.x - radius);
            minY = std::min(minY, center.y - radius);
            maxX = std::max(maxX, center.x + radius);
            maxY = std::max(maxY, center.y + radius);
        }
        else if (shapeName == "RHOMB") {
            Rhomb* rhomb = static_cast<Rhomb*>(shapes_[i].get());
            Point center = rhomb->getCenter();
            double length = rhomb->getLength();
            double width = rhomb->getWidth();

            minX = std::min(minX, center.x - (length / 2));
            minY = std::min(minY, center.y - (width / 2));
            maxX = std::max(maxX, center.x + (length / 2));
            maxY = std::max(maxY, center.y + (width / 2));
        }
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

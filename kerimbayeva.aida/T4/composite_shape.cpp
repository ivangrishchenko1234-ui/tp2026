#include "composite_shape.hpp"
#include <stdexcept>
#include <limits>
#include <iomanip>

void CompositeShape::getBoundingBox(Point& bottomLeft, Point& topRight) const {
    if (shapes_.empty()) {
        bottomLeft = Point(0, 0);
        topRight = Point(0, 0);
        return;
    }

    double xmin = std::numeric_limits<double>::max();
    double ymin = std::numeric_limits<double>::max();
    double xmax = std::numeric_limits<double>::lowest();
    double ymax = std::numeric_limits<double>::lowest();

    for (const auto& shape : shapes_) {
        Point c = shape->getCenter();
        xmin = std::min(xmin, c.x);
        ymin = std::min(ymin, c.y);
        xmax = std::max(xmax, c.x);
        ymax = std::max(ymax, c.y);
    }
    bottomLeft = Point(xmin, ymin);
    topRight = Point(xmax, ymax);
}

double CompositeShape::getArea() const {
    double total = 0.0;
    for (const auto& shape : shapes_) {
        total += shape->getArea();
    }
    return total;
}

Point CompositeShape::getCenter() const {
    if (shapes_.empty()) {
        return Point(0, 0);
    }
    Point bl, tr;
    getBoundingBox(bl, tr);

    return Point((bl.x + tr.x) / 2.0, (bl.y + tr.y) / 2.0);
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

    Point compositeCenter = getCenter();

    for (auto& shape : shapes_) {
        Point shapeCenter = shape->getCenter();

        double dx = shapeCenter.x - compositeCenter.x;
        double dy = shapeCenter.y - compositeCenter.y;

        double newDx = dx * factor;
        double newDy = dy * factor;

        Point newShapeCenter(compositeCenter.x + newDx, compositeCenter.y + newDy);

        double moveX = newShapeCenter.x - shapeCenter.x;
        double moveY = newShapeCenter.y - shapeCenter.y;
        shape->move(moveX, moveY);

        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE_SHAPE";
}

const Shape* CompositeShape::getShape(size_t index) const {
    if (index < shapes_.size()) {
        return shapes_[index].get();
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const CompositeShape& composite) {
    os << composite.getName() << ", (" << std::fixed << std::setprecision(2);
    Point c = composite.getCenter();
    os << c.x << ", " << c.y << "), ";
    os << std::fixed << std::setprecision(2) << composite.getArea() << ":\n";

    for (size_t i = 0; i < composite.getSize(); ++i) {
        os << "    " << *composite.getShape(i);
        if (i < composite.getSize() - 1) {
            os << ",\n";
        }
    }

    return os;
}

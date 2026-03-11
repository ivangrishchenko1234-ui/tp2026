#include "Composite_shape.h"
#include <limits>
#include <iostream>
#include <iomanip>
void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (shape == nullptr) {
        throw std::invalid_argument("Cannot add nullptr shape");
    }
    shapes_.push_back(std::move(shape));
}
double CompositeShape::getArea() const {
    double totalArea = 0.0;
    for (size_t i = 0; i < shapes_.size(); ++i) {
        totalArea += shapes_[i]->getArea();
    }
    return totalArea;
}
Point CompositeShape::getCenter() const {
    if (shapes_.empty()) {
        return Point(0.0, 0.0);
    }
    std::pair<Point, Point> bounds = getBounds();
    double centerX = (bounds.first.x + bounds.second.x) / 2.0;
    double centerY = (bounds.first.y + bounds.second.y) / 2.0;
    return { centerX, centerY };
}
std::pair<Point, Point> CompositeShape::getBounds() const
{
    if (shapes_.empty())
    {
        return { Point(0, 0), Point(0, 0) };
    }

    std::pair<Point, Point> firstFrame = shapes_[0]->getBounds();
    double minX = firstFrame.first.x;
    double minY = firstFrame.first.y;
    double maxX = firstFrame.second.x;
    double maxY = firstFrame.second.y;

    for (size_t i = 1; i < shapes_.size(); ++i)
    {
        std::pair<Point, Point> frame = shapes_[i]->getBounds();
        minX = std::min(minX, frame.first.x);
        minY = std::min(minY, frame.first.y);
        maxX = std::max(maxX, frame.second.x);
        maxY = std::max(maxY, frame.second.y);
    }
    return { Point(minX, minY), Point(maxX, maxY) };
}
void CompositeShape::move(double dx, double dy) {
    for (size_t i = 0; i < shapes_.size(); ++i) {
        shapes_[i]->move(dx, dy);
    }
}
void CompositeShape::scale(double factor) {
    if (shapes_.empty()) return;
    Point compositeCenter = getCenter();
    for (size_t i = 0; i < shapes_.size(); ++i) {
        Point shapeCenter = shapes_[i]->getCenter();

        double dx = shapeCenter.x - compositeCenter.x;
        double dy = shapeCenter.y - compositeCenter.y;

        double newDx = dx * factor;
        double newDy = dy * factor;

        Point newShapeCenter = {
            compositeCenter.x + newDx,
            compositeCenter.y + newDy
        };

        double moveX = newShapeCenter.x - shapeCenter.x;
        double moveY = newShapeCenter.y - shapeCenter.y;
        shapes_[i]->move(moveX, moveY);

        shapes_[i]->scale(factor);
    }
}
std::string CompositeShape::getName() const {
    return "COMPOSITE";
}
void CompositeShape::print(std::ostream& os) const {
    Point center = getCenter();
    os << "[" << getName() << ", (";
    os << std::fixed << std::setprecision(2);
    os << center.x << ", " << center.y << "), ";
    os << getArea() << ": ";
    for (size_t i = 0; i < shapes_.size(); ++i) {
        Point shapeCenter = shapes_[i]->getCenter();
        double shapeArea = shapes_[i]->getArea();
        os << shapes_[i]->getName() << ", ("
            << shapeCenter.x << ", " << shapeCenter.y << "), "
            << shapeArea;
        if (i < shapes_.size() - 1) {
            os << ",";
        }
    }
    os << "]\n";
}

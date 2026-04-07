#include "composite_shape.h"
#include "point.h"
#include <cstddef>
#include <iomanip>
#include <utility>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (shape) {
        shapes.push_back(std::move(shape));
    }
}

double CompositeShape::getArea() const {
    double area = 0.0;
    for (std::size_t i = 0; i < shapes.size(); ++i) {
        area += shapes[i]->getArea();
    }
    return area;
}

Point CompositeShape::getCenter() const {
    std::pair<Point, Point> bounds = getBounds();
    return Point((bounds.first.x + bounds.second.x) / 2.0,
                 (bounds.first.y + bounds.second.y) / 2.0);
}


void CompositeShape::move(double dx, double dy) {
    for (std::size_t i = 0; i < shapes.size(); ++i) {
        shapes[i]->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point compositeCenter = getCenter();

    for (std::size_t i = 0; i < shapes.size(); ++i) {
        Point shapeCenter = shapes[i]->getCenter();

        Point newShapeCenter(
            compositeCenter.x + (shapeCenter.x - compositeCenter.x) * factor,
            compositeCenter.y + (shapeCenter.y - compositeCenter.y) * factor
        );

        shapes[i]->move(
            newShapeCenter.x - shapeCenter.x,
            newShapeCenter.y - shapeCenter.y
        );

        shapes[i]->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

std::pair<Point, Point> CompositeShape::getBounds() const {
    if (shapes.empty()) {
        throw std::logic_error("CompositeShape is empty");
    }

    std::pair<Point, Point> temp = shapes[0]->getBounds();
    Point temp_min = temp.first;
    Point temp_max = temp.second;

    for (std::size_t i = 1; i < shapes.size(); ++i) {
        std::pair<Point, Point> current = shapes[i]->getBounds();
        Point cur_min = current.first;
        Point cur_max = current.second;

        temp_min.x = (cur_min.x < temp_min.x) ? cur_min.x : temp_min.x;
        temp_min.y = (cur_min.y < temp_min.y) ? cur_min.y : temp_min.y;
        temp_max.x = (cur_max.x > temp_max.x) ? cur_max.x : temp_max.x;
        temp_max.y = (cur_max.y > temp_max.y) ? cur_max.y : temp_max.y;
    }

    return std::make_pair(Point(temp_min.x, temp_min.y), Point(temp_max.x, temp_max.y));
}

void CompositeShape::print(std::ostream& stream) const {
    Point center = getCenter();
    stream << "[";
    stream << getName() << ", ";
    stream << "(" << center.x << ", " << center.y << ")" << ", ";
    stream << getArea() << ":\n";

    for (const auto& shape : shapes) {
        stream << std::setw(4);
        shape->print(stream);
        stream << ",\n";
    }
    stream << "]";
}

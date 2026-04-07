#include "CompositeShape.h"
#include "Shape.h"
#include <memory>
#include <limits>
#include <iomanip>
#include <stdexcept>

double CompositeShape::getArea() const {
    double res = 0.0;
    for (const auto& s : shapes_) {
        res += s->getArea();
    }
    return res;
}

Point CompositeShape::getCenter() const {
    if (shapes_.empty()) {
        return Point(0.0, 0.0);
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto& s : shapes_) {
        Point p = s->getBottomLeft();
        minX = p.x_ < minX ? p.x_ : minX;
        minY = p.y_ < minY ? p.y_ : minY;

        Point k = s->getTopRight();
        maxX = k.x_ > maxX ? k.x_ : maxX;
        maxY = k.y_ > maxY ? k.y_ : maxY;
    }

    double centerX = (maxX - minX) / 2.0 + minX;
    double centerY = (maxY - minY) / 2.0 + minY;
    return Point(centerX, centerY);
}

void CompositeShape::move(double x, double y) {
    for (auto& s : shapes_) {
        s->move(x, y);
    }
}

void CompositeShape::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("CompositeShape::scale: scale factor must be positive");
    }
    Point center = getCenter();

    for (auto& s : shapes_) {
        Point oldCenter = s->getCenter();

        double newX = center.x_ + factor * (oldCenter.x_ - center.x_);
        double newY = center.y_ + factor * (oldCenter.y_ - center.y_);

        s->scale(factor);

        s->move(newX - oldCenter.x_, newY - oldCenter.y_);
    }
}

std::string CompositeShape::getName() const {
    return std::string("Composite Shape\n");
}

void CompositeShape::addShape(std::unique_ptr<Shape> other) {
    shapes_.push_back(std::move(other));
}

const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const {
    return shapes_;
}

void CompositeShape::print(std::ostream& stream) const {
    stream << std::fixed << std::setprecision(2) << "[COMPOSITE, (" <<
        this->getCenter().x_ << ", " << this->getCenter().y_ << "), " <<
        this->getArea() << ":";
    for (const auto& s : shapes_) {
        stream << "\n " << s->getName();
        stream << ", (" << s->getCenter().x_ << ", " << s->getCenter().y_ << "), ";
        stream << s->getArea() << ";";
    }
    stream << "\n]\n";
}

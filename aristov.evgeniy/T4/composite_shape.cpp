#include "composite_shape.h"
#include "utils.h"
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <sstream>
#include <iomanip>

CompositeShape::CompositeShape(const CompositeShape& other) {
    shapes_.reserve(other.shapes_.size());
    for (const auto& shape : other.shapes_) {
        shapes_.push_back(shape->clone());
    }
}

CompositeShape& CompositeShape::operator=(const CompositeShape& other) {
    if (this != &other) {
        CompositeShape temp(other);
        std::swap(shapes_, temp.shapes_);
    }
    return *this;
}

double CompositeShape::getArea() const {
    double totalArea = 0.0;
    for (const auto& shape : shapes_) {
        totalArea += shape->getArea();
    }
    return totalArea;
}

FrameRect CompositeShape::getFrameRect() const {
    if (shapes_.empty()) {
        return {0.0, 0.0, {0.0, 0.0}};
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto& shape : shapes_) {
        FrameRect fr = shape->getFrameRect();
        minX = std::min(minX, fr.pos.x - fr.width / 2.0);
        minY = std::min(minY, fr.pos.y - fr.height / 2.0);
        maxX = std::max(maxX, fr.pos.x + fr.width / 2.0);
        maxY = std::max(maxY, fr.pos.y + fr.height / 2.0);
    }

    return {maxX - minX, maxY - minY, {(minX + maxX) / 2.0, (minY + maxY) / 2.0}};
}

Point CompositeShape::getCenter() const {
    return getFrameRect().pos;
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes_) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (factor <= 0.0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    Point compCenter = getCenter();
    for (auto& shape : shapes_) {
        Point shapeCenter = shape->getCenter();
        double dx = shapeCenter.x - compCenter.x;
        double dy = shapeCenter.y - compCenter.y;

        shape->move(dx * (factor - 1.0), dy * (factor - 1.0));
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

std::string CompositeShape::toString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    Point c = getCenter();

    oss << "[" << getName() << ", (" << c.x << ", " << c.y << "), " << getArea();

    if (!shapes_.empty()) {
        oss << ":";
        for (size_t i = 0; i < shapes_.size(); ++i) {
            std::string inner = shapes_[i]->toString();

            if (inner.length() >= 2 && inner.front() == '[' && inner.back() == ']') {
                inner = inner.substr(1, inner.length() - 2);
            }

            size_t pos = 0;
            while ((pos = inner.find('\n', pos)) != std::string::npos) {
                inner.replace(pos, 1, "\n  ");
                pos += 3;
            }

            oss << "\n  " << inner;

            if (i < shapes_.size() - 1) {
                oss << ",";
            }
        }
        oss << "\n";
    }
    oss << "]";
    return oss.str();
}

std::unique_ptr<Shape> CompositeShape::clone() const {
    return std::make_unique<CompositeShape>(*this);
}

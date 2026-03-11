#include "composite-shape.h"
#include <stdexcept>
#include <algorithm>

void CompositeShape::add(std::unique_ptr<Shape> s) {
    if (!s) throw std::invalid_argument("Shape is null");

    if (dynamic_cast<CompositeShape*>(s.get())) {
        throw std::invalid_argument("Cannot add composite shape to another composite");
    }

    shapes_.push_back(std::move(s));
}

double CompositeShape::getArea() const {
    double total = 0;
    for (const auto& s : shapes_) total += s->getArea();
    return total;
}

Point CompositeShape::getCenter() const {
    if (shapes_.empty()) throw std::logic_error("Empty composite");

    double minX = shapes_[0]->getMinX();
    double maxX = shapes_[0]->getMaxX();
    double minY = shapes_[0]->getMinY();
    double maxY = shapes_[0]->getMaxY();

    for (size_t i = 1; i < shapes_.size(); ++i) {
        minX = std::min(minX, shapes_[i]->getMinX());
        maxX = std::max(maxX, shapes_[i]->getMaxX());
        minY = std::min(minY, shapes_[i]->getMinY());
        maxY = std::max(maxY, shapes_[i]->getMaxY());
    }

    return { (minX + maxX) / 2.0, (minY + maxY) / 2.0 };
}

void CompositeShape::move(double dx, double dy) {
    for (auto& s : shapes_) s->move(dx, dy);
}

void CompositeShape::move(const Point& nc) {
    Point current = getCenter();
    move(nc.x - current.x, nc.y - current.y);
}

void CompositeShape::scale(double k) {
    if (k <= 0) throw std::invalid_argument("Scale must be > 0");
    Point globalCenter = getCenter();
    for (auto& s : shapes_) {
        Point childCenter = s->getCenter();

        double newX = globalCenter.x + (childCenter.x - globalCenter.x) * k;
        double newY = globalCenter.y + (childCenter.y - globalCenter.y) * k;
        s->move({ newX, newY });
        s->scale(k);
    }
}

std::string CompositeShape::getName() const { return "COMPOSITE"; }

double CompositeShape::getMinX() const {
    if (shapes_.empty()) throw std::logic_error("Empty composite");
    double minX = shapes_[0]->getMinX();
    for (size_t i = 1; i < shapes_.size(); ++i) {
        minX = std::min(minX, shapes_[i]->getMinX());
    }
    return minX;
}

double CompositeShape::getMaxX() const {
    if (shapes_.empty()) throw std::logic_error("Empty composite");
    double maxX = shapes_[0]->getMaxX();
    for (size_t i = 1; i < shapes_.size(); ++i) {
        maxX = std::max(maxX, shapes_[i]->getMaxX());
    }
    return maxX;
}

double CompositeShape::getMinY() const {
    if (shapes_.empty()) throw std::logic_error("Empty composite");
    double minY = shapes_[0]->getMinY();
    for (size_t i = 1; i < shapes_.size(); ++i) {
        minY = std::min(minY, shapes_[i]->getMinY());
    }
    return minY;
}

double CompositeShape::getMaxY() const {
    if (shapes_.empty()) throw std::logic_error("Empty composite");
    double maxY = shapes_[0]->getMaxY();
    for (size_t i = 1; i < shapes_.size(); ++i) {
        maxY = std::max(maxY, shapes_[i]->getMaxY());
    }
    return maxY;
}

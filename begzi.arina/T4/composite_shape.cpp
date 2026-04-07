#include "composite_shape.h"
#include <iostream>
#include <algorithm>

void CompositeShape::add(std::unique_ptr<Shape> s) {
    if (s != nullptr) {
        shapes.push_back(std::move(s));
    }
}

double CompositeShape::getArea() const {
    double total = 0.0;
    for (size_t i = 0; i < shapes.size(); i++) {
        total = total + shapes[i]->getArea();
    }
    return total;
}

void CompositeShape::getBoundingBox(Point& bl, Point& tr) const {
    if (shapes.empty()) {
        bl = { 0, 0 };
        tr = { 0, 0 };
        return;
    }
    shapes[0]->getBoundingBox(bl, tr);
    for (size_t i = 1; i < shapes.size(); i++) {
        Point b, t;
        shapes[i]->getBoundingBox(b, t);
        bl.x = std::min(bl.x, b.x);
        bl.y = std::min(bl.y, b.y);
        tr.x = std::max(tr.x, t.x);
        tr.y = std::max(tr.y, t.y);
    }
}

Point CompositeShape::getCenter() const {
    Point bl, tr;
    getBoundingBox(bl, tr);
    return { (bl.x + tr.x) / 2.0, (bl.y + tr.y) / 2.0 };
}

void CompositeShape::move(double dx, double dy) {
    for (size_t i = 0; i < shapes.size(); i++) {
        shapes[i]->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point baseC = getCenter();
    for (size_t i = 0; i < shapes.size(); i++) {
        Point itemC = shapes[i]->getCenter();
        double dx = (itemC.x - baseC.x) * (factor - 1.0);
        double dy = (itemC.y - baseC.y) * (factor - 1.0);
        shapes[i]->move(dx, dy);
        shapes[i]->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

void CompositeShape::print() const {
    Shape::print();
    for (size_t i = 0; i < shapes.size(); i++) {
        std::cout << "\n";
        shapes[i]->print();
    }
}

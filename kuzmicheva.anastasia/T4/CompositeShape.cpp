#include "CompositeShape.h"
#include <iostream>
#include <stdexcept>

void CompositeShape::add(std::unique_ptr<Shape> figure) {
    shapes.push_back(std::move(figure));
}

double CompositeShape::getArea() const {
    double areas = 0;
    for (size_t i = 0; i < shapes.size(); i++) {
        areas += shapes[i]->getArea();
    }
    return areas;
}

Point CompositeShape::getCenter() const {
    if (shapes.empty()) {
        return Point(0.0, 0.0);
    }
    double c_x = 0;
    double c_y = 0;
    for (size_t i = 0; i < shapes.size(); i++) {
        c_x += shapes[i]->getCenter().x;
        c_y += shapes[i]->getCenter().y;
    }
    return Point(c_x / shapes.size(), c_y / shapes.size());
}

void CompositeShape::move(double dx, double dy) {
    for (size_t i = 0; i < shapes.size(); i++) {
        shapes[i]->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Error: scale factor must be positive\n");
    }

    Point compositeCenter = this->getCenter();

    for (size_t i = 0; i < shapes.size(); i++) {

        Point shapeCenter = shapes[i]->getCenter();

        double dx = shapeCenter.x - compositeCenter.x;
        double dy = shapeCenter.y - compositeCenter.y;

        double newDx = dx * factor;
        double newDy = dy * factor;

        Point newShapeCenter = Point(compositeCenter.x + newDx, compositeCenter.y + newDy);

        double moveX = newShapeCenter.x - shapeCenter.x;
        double moveY = newShapeCenter.y - shapeCenter.y;
        shapes[i]->move(moveX, moveY);

        shapes[i]->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "Composite";
}

void CompositeShape::info() const {
    if (shapes.empty()) {
        std::cout << "[Composite, (0.0, 0.0), 0]" << '\n';
    }
    else {
        std::cout << "[" << "Composite, " << "(" << getCenter().x << ", " << getCenter().y << "), "
            << getArea() << ":" << '\n';
        for (size_t i = 0; i < shapes.size(); i++) {
            std::cout << shapes[i]->getName() << ", " << "(" << shapes[i]->getCenter().x << ", "
                << shapes[i]->getCenter().y << "), " << shapes[i]->getArea() << '\n';
        }
        std::cout << ']' << '\n';
    }
}

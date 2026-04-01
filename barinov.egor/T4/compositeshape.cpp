#include "compositeshape.h"
#include <algorithm>
#include <limits>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double totalArea = 0;
    for (const auto& shape : shapes) {
        totalArea += shape->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const {
    if (shapes.empty()) {
        return Point(0, 0);
    }
    
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();
    
    for (const auto& shape : shapes) {
        BoundingBox box = shape->getBoundingBox();
        
        minX = std::min(minX, box.bottomLeft.x);
        minY = std::min(minY, box.bottomLeft.y);
        maxX = std::max(maxX, box.topRight.x);
        maxY = std::max(maxY, box.topRight.y);
    }
    
    return Point((minX + maxX) / 2, (minY + maxY) / 2);
}

BoundingBox CompositeShape::getBoundingBox() const {
    if (shapes.empty()) {
        BoundingBox emptyBox;
        emptyBox.bottomLeft = Point(0, 0);
        emptyBox.topRight = Point(0, 0);
        return emptyBox;
    }
    
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();
    
    for (const auto& shape : shapes) {
        BoundingBox box = shape->getBoundingBox();
        
        minX = std::min(minX, box.bottomLeft.x);
        minY = std::min(minY, box.bottomLeft.y);
        maxX = std::max(maxX, box.topRight.x);
        maxY = std::max(maxY, box.topRight.y);
    }
    
    BoundingBox resultBox;
    resultBox.bottomLeft = Point(minX, minY);
    resultBox.topRight = Point(maxX, maxY);
    return resultBox;
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point compositeCenter = getCenter();
    
    for (auto& shape : shapes) {
        Point shapeCenter = shape->getCenter();
        
        double dx = shapeCenter.x - compositeCenter.x;
        double dy = shapeCenter.y - compositeCenter.y;
        
        shape->move(dx * (factor - 1), dy * (factor - 1));
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const {
    return shapes;
}


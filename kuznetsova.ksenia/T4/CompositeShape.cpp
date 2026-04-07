#include "CompositeShape.h"
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <cmath>

CompositeShape::CompositeShape(const CompositeShape& other) {
for (const auto& shape : other.shapes_) {
shapes_.push_back(shape->clone());
}
}

CompositeShape& CompositeShape::operator=(const CompositeShape& other) {
if (this != &other) {
shapes_.clear();
for (const auto& shape : other.shapes_) {
shapes_.push_back(shape->clone());
}
}
return *this;
}

CompositeShape::CompositeShape(CompositeShape&& other) noexcept
: shapes_(std::move(other.shapes_)) {
}

CompositeShape& CompositeShape::operator=(CompositeShape&& other) noexcept {
if (this != &other) {
shapes_ = std::move(other.shapes_);
}
return *this;
}

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
shapes_.push_back(std::move(shape));
}

Shape* CompositeShape::getShape(size_t index) const {
if (index >= shapes_.size()) {
throw std::out_of_range("Index out of range");
}
return shapes_[index].get();
}

void CompositeShape::getBoundingBox(Point& min, Point& max) const {
if (isEmpty()) {
min = Point(0, 0);
max = Point(0, 0);
return;
}

min.x = std::numeric_limits<double>::max();
min.y = std::numeric_limits<double>::max();
max.x = -std::numeric_limits<double>::max();
max.y = -std::numeric_limits<double>::max();

for (const auto& shape : shapes_) {
Point center = shape->getCenter();
min.x = std::min(min.x, center.x);
min.y = std::min(min.y, center.y);
max.x = std::max(max.x, center.x);
max.y = std::max(max.y, center.y);
}
}

double CompositeShape::getArea() const {
double totalArea = 0.0;
for (const auto& shape : shapes_) {
totalArea += shape->getArea();
}
return totalArea;
}

Point CompositeShape::getCenter() const {
if (shapes_.empty()) {
return Point(0.0, 0.0);
}
Point min, max;
getBoundingBox(min, max);
return Point((min.x + max.x) / 2.0, (min.y + max.y) / 2.0);
}

void CompositeShape::move(double dx, double dy) {
for (auto& shape : shapes_) {
shape->move(dx, dy);
}
}

void CompositeShape::scale(double factor) {
if (isEmpty()) return;

Point compositeCenter = getCenter();

for (auto& shape : shapes_) {
Point shapeCenter = shape->getCenter();

double dx = shapeCenter.x - compositeCenter.x;
double dy = shapeCenter.y - compositeCenter.y;

double newDx = dx * factor;
double newDy = dy * factor;

Point newShapeCenter(
compositeCenter.x + newDx,
compositeCenter.y + newDy
);

double moveX = newShapeCenter.x - shapeCenter.x;
double moveY = newShapeCenter.y - shapeCenter.y;
shape->move(moveX, moveY);

shape->scale(factor);
}
}

std::string CompositeShape::getName() const {
return "COMPOSITE";
}

std::unique_ptr<Shape> CompositeShape::clone() const {
auto copy = std::make_unique<CompositeShape>();
for (const auto& shape : shapes_) {
copy->addShape(shape->clone());
}
return copy;
}

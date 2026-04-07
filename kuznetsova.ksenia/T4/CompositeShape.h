#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "Shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
public:
CompositeShape() = default;
~CompositeShape() override = default;

CompositeShape(const CompositeShape& other);
CompositeShape& operator=(const CompositeShape& other);
CompositeShape(CompositeShape&& other) noexcept;
CompositeShape& operator=(CompositeShape&& other) noexcept;

void addShape(std::unique_ptr<Shape> shape);
Shape* getShape(size_t index) const;
size_t getSize() const { return shapes_.size(); }
bool isEmpty() const { return shapes_.empty(); }

double getArea() const override;
Point getCenter() const override;
void move(double dx, double dy) override;
void scale(double factor) override;
std::string getName() const override;
std::unique_ptr<Shape> clone() const override;

void getBoundingBox(Point& min, Point& max) const;

private:
std::vector<std::unique_ptr<Shape>> shapes_;
};

#endif

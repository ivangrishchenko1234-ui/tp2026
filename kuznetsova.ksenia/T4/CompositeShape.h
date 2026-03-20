#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "Shape.h"
#include <vector>
#include <memory>
#include <utility>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes_;

    void getBoundingBox(Point& min, Point& max) const;

public:
    CompositeShape() = default;

    void addShape(std::unique_ptr<Shape> shape);
    size_t getSize() const { return shapes_.size(); }
    bool isEmpty() const { return shapes_.empty(); }
    Shape* getShape(size_t index) const;

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif

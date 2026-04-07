#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "shape.h"
#include <memory>
#include <vector>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes_;
    std::pair<Point, Point> getBounds() const;
public:
    CompositeShape() = default;
    CompositeShape(const CompositeShape&) = delete;
    CompositeShape& operator=(const CompositeShape&) = delete;
    CompositeShape(CompositeShape&&) = default;
    CompositeShape& operator=(CompositeShape&&) = default;
    void addShape(std::unique_ptr<Shape> shape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif

#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include <vector>
#include <memory>
#include "shape.h"

class CompositeShape : public Shape {
public:
    void addShape(std::unique_ptr<Shape> shape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void move(const Point &newCenter) override;
    void scale(double factor) override;
    std::string getName() const override;
    size_t getSize() const;
    const Shape* getShape(size_t index) const;

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};

#endif

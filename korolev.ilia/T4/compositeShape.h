#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "shape.h"
#include <vector>
#include <memory>
#include <ostream>

class CompositeShape : public Shape
{
public:
    CompositeShape();
    void addShape(std::unique_ptr<Shape> shape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    const char* getName() const override;
    void printDetails(std::ostream& out) const;

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};

#endif

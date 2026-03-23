#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "shape.h"
#include <memory>
#include <vector>

class CompositeShape : public Shape
{
private:
    std::vector<std::shared_ptr<Shape>> shapes_;

public:
    CompositeShape() = default;

    void addShape(const std::shared_ptr<Shape>& shape);

    double getArea() const override;
    Point getCenter() const override;
    void move(const Point& newCenter) override;
    void scale(double ratio) override;
    std::string getName() const override;
};

#endif

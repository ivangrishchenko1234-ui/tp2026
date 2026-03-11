#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "Shape.hpp"
#include <memory>
#include <vector>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes_;

public:
    CompositeShape() {}
    ~CompositeShape() {}

    void addShape(std::unique_ptr<Shape> shape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    const std::vector<std::unique_ptr<Shape>>& getShapes() const;
};

#endif

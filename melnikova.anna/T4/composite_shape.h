#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes_;
public:
    CompositeShape() = default;
    explicit CompositeShape(std::vector<std::unique_ptr<Shape>> shapes);
    std::size_t size() const;
    const Shape& getShape(std::size_t index) const;
    void addShape(std::unique_ptr<Shape> shape);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double coeff) override;
    std::string getName() const override;
    RectanglePoints getBorderRectangle() const override;
};

#endif

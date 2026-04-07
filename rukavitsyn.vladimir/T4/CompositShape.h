#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include "Shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes;

public:
    CompositeShape() = default;
    CompositeShape(const CompositeShape&) = delete;
    CompositeShape(CompositeShape&&) noexcept = default;
    CompositeShape& operator=(const CompositeShape&) = delete;
    CompositeShape& operator=(CompositeShape&&) noexcept = default;
    ~CompositeShape() noexcept override = default;

    void addShape(std::unique_ptr<Shape> shape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::pair<Point, Point> circumscribedRectangle() const override;
    std::string getName() const override;
    void print(std::ostream& stream) const override;
};

#endif

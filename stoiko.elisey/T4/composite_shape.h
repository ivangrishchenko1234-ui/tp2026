#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "point.h"
#include "shape.h"
#include <memory>
#include <string>
#include <vector>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes;
public:
    CompositeShape() = default;
    CompositeShape(const CompositeShape& other) = delete;
    CompositeShape(CompositeShape&& other) noexcept = default;
    CompositeShape& operator=(const CompositeShape& other) = delete;
    CompositeShape& operator=(CompositeShape&& other) noexcept = default;
    ~CompositeShape() override = default;

    void addShape(std::unique_ptr<Shape> shape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    std::pair<Point, Point> getBounds() const override;
    void print(std::ostream& stream) const override;
};

#endif // COMPOSITE_SHAPE_H

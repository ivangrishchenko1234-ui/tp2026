#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H
#include "shape.h"
#include "point.h"
#include <memory>
#include <string>
#include <vector>

class CompositeShape : public Shape
{
public:
    CompositeShape() = default;
    CompositeShape(const CompositeShape&) = delete;
    CompositeShape& operator=(const CompositeShape&) = delete;
    CompositeShape(CompositeShape&&) = default;
    CompositeShape& operator=(CompositeShape&&) = default;
    ~CompositeShape() = default;

    void addShape(std::unique_ptr<Shape> newShape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> getFrame() const override;
    const std::vector<std::unique_ptr<Shape>>& getShapes() const;
private:
    std::vector<std::unique_ptr<Shape>> shapes;
};

#endif

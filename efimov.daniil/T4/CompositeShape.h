#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H
#include "Shape.h"
#include "Point.h"
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

    ~CompositeShape() override = default;

    void addShape(std::unique_ptr<Shape> shape);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> getFrame() const override;

    const std::vector<std::unique_ptr<Shape>>& getShapes() const { return shapes; }

    bool isEmpty() const { return shapes.empty(); }
    size_t getSize() const { return shapes.size(); }

private:
    std::vector<std::unique_ptr<Shape>> shapes;
};

#endif

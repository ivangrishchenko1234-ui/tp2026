#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H
#include "shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes;
public:
    CompositeShape() = default;
    CompositeShape(const CompositeShape& other) = delete;
    CompositeShape& operator=(const CompositeShape& other) = delete;
    CompositeShape(CompositeShape&& other) = default;
    CompositeShape& operator=(CompositeShape&& other) = default;
    void addShape(std::unique_ptr<Shape> shape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    void print() const override;
};

#endif



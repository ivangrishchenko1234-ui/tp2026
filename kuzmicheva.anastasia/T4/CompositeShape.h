#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include <vector>
#include <string>
#include <memory>
#include "Shape.h"

class CompositeShape : public Shape {
public:
    ~CompositeShape() override = default;
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    void add(std::unique_ptr<Shape> figure);
    void info() const override;
private:
    std::vector<std::unique_ptr<Shape>> shapes;
};

#endif

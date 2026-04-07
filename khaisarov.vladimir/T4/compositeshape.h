#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include "shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape
{

private:
    std::vector<std::unique_ptr<Shape>> shapes;
public:
    CompositeShape() = default;
    CompositeShape(std::vector<std::unique_ptr<Shape>>&& s);
    double getArea() const override;
    Point getCenter() const override;
    std::string getName() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::pair<Point, Point> Bounds() const override;
    void print(std::ostream& os) const;
    void add(std::unique_ptr<Shape> shape);
};

#endif

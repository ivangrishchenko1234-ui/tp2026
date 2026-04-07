#ifndef COMPOSITE_H
#define COMPOSITE_H
#include "shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes;

public:
    void add(std::unique_ptr<Shape> s);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    void getBoundingBox(Point& bl, Point& tr) const override;
    void print() const override;
};

#endif

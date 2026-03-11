#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H
#include <vector>
#include <memory>
#include "shape.h"

class CompositeShape : public Shape {
public:
    void add(std::unique_ptr<Shape> s);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void move(const Point& nc) override;
    void scale(double k) override;
    std::string getName() const override;

    double getMinX() const override;
    double getMaxX() const override;
    double getMinY() const override;
    double getMaxY() const override;

    const std::vector<std::unique_ptr<Shape>>& getShapes() const { return shapes_; }

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};
#endif

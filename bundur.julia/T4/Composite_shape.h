#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H
#include <vector>
#include <memory>
#include "Shape.h"
class CompositeShape : public Shape {
private:
    std::vector<std::shared_ptr<Shape>> shapes_;
public:
    void addShape(std::shared_ptr<Shape> shape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    const std::vector<std::shared_ptr<Shape>>& getShapes() const;
};
#endif


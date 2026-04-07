#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H
#include "Shape.h"
#include <iostream>
#include <vector>
#include <memory>
class CompositeShape : public Shape
{
public:
    void addShape(std::unique_ptr<Shape> shape);
    double getArea() override;
    Point getCenter() override;
    void move(double x_, double y_) override;
    void scale(double k) override;
    std::string getName() override;
    double getX_min() override;
    double getX_max() override;
    double getY_min() override;
    double getY_max() override;
    void print() override;
private:
    std::vector<std::unique_ptr<Shape>> shapes;
};
#endif

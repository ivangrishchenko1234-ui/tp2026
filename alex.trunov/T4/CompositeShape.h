#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include "Shape.h"

#ifndef COMPOSITE_SHAPE
#define COMPOSITE_SHAPE

class CompositeShape : public Shape {
public:
    double getArea() const override;
    Point getCenter() const override;
    void move(double x, double y) override;
    void scale(double factor) override;
    std::string getName() const override;

    void addShape(std::unique_ptr<Shape> other);
    const std::vector<std::unique_ptr<Shape>>& getShapes() const;
    void print(std::ostream& stream) const;

    Point getTopRight() const override { return Point(0, 0); }
    Point getBottomLeft() const override { return Point(0, 0); }
private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};

#endif

#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include "shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes;
    
public:
    void addShape(std::unique_ptr<Shape> shape);
    
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    BoundingBox getBoundingBox() const override;
    
    const std::vector<std::unique_ptr<Shape>>& getShapes() const;
};

#endif


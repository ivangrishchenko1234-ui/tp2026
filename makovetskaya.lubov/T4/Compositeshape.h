#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include "Shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
public:
    void addShape(std::shared_ptr<Shape> shape);
    void removeShape(std::shared_ptr<Shape> shape);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    size_t getCount() const;
    const std::vector<std::shared_ptr<Shape>>& getShapes() const;

private:
    std::vector<std::shared_ptr<Shape>> shapes;
    void getBoundingBox(double& minX, double& minY, double& maxX, double& maxY) const;
};

#endif

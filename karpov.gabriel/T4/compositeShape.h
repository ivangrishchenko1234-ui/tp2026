#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include "shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes_;
    void getBoundingBox(double& minX, double& minY,
                        double& maxX, double& maxY) const;
public:
    CompositeShape() = default;
    CompositeShape(const CompositeShape& other) = delete;
    CompositeShape(CompositeShape&& other) noexcept = default;
    CompositeShape& operator=(const CompositeShape& other) = delete;
    CompositeShape& operator=(CompositeShape&& other) noexcept = default;
    ~CompositeShape() override = default;
    void addShape(std::unique_ptr<Shape> shape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    double getMinX() const override;
    double getMinY() const override;
    double getMaxX() const override;
    double getMaxY() const override;
};

#endif

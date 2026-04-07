#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H
#include <string>
#include <vector>
#include <memory>
#include "point.h"
#include "shape.h"

class CompositeShape : public Shape {
public:
    double getArea() const override;
    Point getCenter() const override;
    void move(double a, double b) override;
    void scale(double c) override;
    std::string getName() const override;
    void addShape(std::unique_ptr<Shape> shape);
    void getBoundingBox(double& minX, double& minY,
                        double& maxX, double& maxY) const override;
    friend std::ostream& operator<<(std::ostream& os, const CompositeShape& composite);
private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};
#endif

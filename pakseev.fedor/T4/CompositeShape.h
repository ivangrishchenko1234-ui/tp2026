#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include "Shape.h"

#include <vector>
#include <memory>

class CompositeShape : public Shape {
public:
    CompositeShape() = default;

    template<class T>
    explicit CompositeShape(std::unique_ptr<T>&& shape) { add(std::move(shape)); }
    ~CompositeShape() override = default;

    template<class T>
    void push_back(std::unique_ptr<T>&& shape) { add(std::move(shape)); }
    std::string getName() const override { return "Composite"; }
    Point getCenter() const override;
    double getArea() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    const std::vector<std::unique_ptr<Shape>>& getVec() const { return vec_; }
private:
    std::vector<std::unique_ptr<Shape>> vec_ = {};

    void add(std::unique_ptr<Shape> shape) {
        if (shape && shape->getName() != "Composite") {
            vec_.push_back(std::move(shape));
        }
    }
};

#endif

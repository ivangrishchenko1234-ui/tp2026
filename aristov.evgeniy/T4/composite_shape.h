#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "shape.h"
#include <vector>
#include <memory>
#include <type_traits>

class CompositeShape : public Shape {
public:
    CompositeShape() = default;
    CompositeShape(const CompositeShape& other);
    CompositeShape(CompositeShape&& other) noexcept = default;
    CompositeShape& operator=(const CompositeShape& other);
    CompositeShape& operator=(CompositeShape&& other) noexcept = default;
    ~CompositeShape() override = default;

    template <typename T, typename = std::enable_if_t<std::is_base_of<Shape, T>::value>>
    void addShape(std::unique_ptr<T> shape) {
        if (shape) {
            shapes_.push_back(std::move(shape));
        }
    }

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    FrameRect getFrameRect() const override;
    std::string toString() const override;
    std::unique_ptr<Shape> clone() const override;

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};

#endif

#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes_;

    void getBoundingBox(Point& bottomLeft, Point& topRight) const;

public:
    CompositeShape() = default;

    CompositeShape(const CompositeShape&) = delete;
    CompositeShape& operator=(const CompositeShape&) = delete;

    CompositeShape(CompositeShape&&) = default;
    CompositeShape& operator=(CompositeShape&&) = default;

    template<typename T, typename... Args>
    void addShape(Args&&... args) {
        shapes_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    size_t getSize() const { return shapes_.size(); }
    const Shape* getShape(size_t index) const;
};
std::ostream& operator<<(std::ostream& os, const CompositeShape& composite);

#endif

#include "composite_shape.h"

CompositeShape::CompositeShape(std::vector<std::unique_ptr<Shape>> shapes) :
    shapes_(std::move(shapes))
{
    for (const std::unique_ptr<Shape>& sh : shapes_) {
        if (!sh) {
            throw std::invalid_argument("CompositeShape: nullptr shape");
        }
    }
}

size_t CompositeShape::size() const
{
    return shapes_.size();
}

const Shape& CompositeShape::getShape(std::size_t index) const
{
    if (index >= shapes_.size()) {
        throw std::out_of_range("CompositeShape (getShape): index out of range");
    }
    return *shapes_[index];
}

void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
    if (!shape) {
        throw std::invalid_argument("CompositeShape (addShape): nullptr shape");
    }
    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const
{
    double totalArea = 0;
    for (const std::unique_ptr<Shape>& sh : shapes_) {
        totalArea += sh->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const
{
    RectanglePoints border = getBorderRectangle();
    return {
        (border.leftBottom_.x + border.rightTop_.x) / 2,
        (border.leftBottom_.y + border.rightTop_.y) / 2
    };
}

void CompositeShape::move(double dx, double dy)
{
    for (const std::unique_ptr<Shape>& sh : shapes_) {
        sh->move(dx, dy);
    }
}

void CompositeShape::scale(double coeff)
{
    if (coeff <= 0.0) {
        throw std::invalid_argument("CompositeShape (scale): coefficient must be positive");
    }
    Point center = getCenter();
    for (std::unique_ptr<Shape>& s : shapes_) {
        s->scale(coeff);
        Point sc = s->getCenter();
        double newCx = center.x + (sc.x - center.x) * coeff;
        double newCy = center.y + (sc.y - center.y) * coeff;
        s->move(newCx - sc.x, newCy - sc.y);
    }
}

std::string CompositeShape::getName() const
{
    return "COMPOSITE";
}

RectanglePoints CompositeShape::getBorderRectangle() const
{
    if (shapes_.empty()) {
        return { {0, 0}, {0, 0} };
    }
    double xmin = shapes_[0]->getBorderRectangle().leftBottom_.x;
    double ymin = shapes_[0]->getBorderRectangle().leftBottom_.y;
    double xmax = shapes_[0]->getBorderRectangle().rightTop_.x;
    double ymax = shapes_[0]->getBorderRectangle().rightTop_.y;

    for (const std::unique_ptr<Shape>& sh : shapes_) {
        xmin = std::min(xmin, sh->getBorderRectangle().leftBottom_.x);
        ymin = std::min(ymin, sh->getBorderRectangle().leftBottom_.y);
        xmax = std::max(xmax, sh->getBorderRectangle().rightTop_.x);
        ymax = std::max(ymax, sh->getBorderRectangle().rightTop_.y);
    }
    return { {xmin, ymin}, {xmax, ymax} };
}

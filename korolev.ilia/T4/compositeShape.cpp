#include "compositeShape.h"
#include <algorithm>
#include <limits>
#include <iomanip>
#include <cmath>

CompositeShape::CompositeShape()
{
}

void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const
{
    double totalArea = 0.0;
    for (const auto& shape : shapes_)
    {
        totalArea = totalArea + shape->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const
{
    if (shapes_.empty())
    {
        return Point(0.0, 0.0);
    }

    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto& shape : shapes_)
    {
        Point center = shape->getCenter();
        double area = shape->getArea();
        double halfSize = std::sqrt(area) / 2.0;
        double left = center.x_ - halfSize;
        double right = center.x_ + halfSize;
        double bottom = center.y_ - halfSize;
        double top = center.y_ + halfSize;
        minX = std::min(minX, left);
        maxX = std::max(maxX, right);
        minY = std::min(minY, bottom);
        maxY = std::max(maxY, top);
    }

    double centerX = (minX + maxX) / 2.0;
    double centerY = (minY + maxY) / 2.0;
    return Point(centerX, centerY);
}

void CompositeShape::move(double dx, double dy)
{
    for (auto& shape : shapes_)
    {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor)
{
    Point center = getCenter();
    for (auto& shape : shapes_)
    {
        Point shapeCenter = shape->getCenter();
        double moveX = (shapeCenter.x_ - center.x_) * (factor - 1.0);
        double moveY = (shapeCenter.y_ - center.y_) * (factor - 1.0);
        shape->move(moveX, moveY);
        shape->scale(factor);
    }
}

const char* CompositeShape::getName() const
{
    return "COMPOSITE";
}

void CompositeShape::printDetails(std::ostream& out) const
{
    out << std::fixed << std::setprecision(2);
    Point center = getCenter();
    out << "[COMPOSITE,(" << center.x_ << ", " << center.y_ << "), "
        << getArea() << ": ";
    for (size_t i = 0; i < shapes_.size(); ++i)
    {
        if (i > 0)
        {
            out << ", ";
        }
        Point shapeCenter = shapes_[i]->getCenter();
        out << shapes_[i]->getName() << ",(" << shapeCenter.x_ << ", "
            << shapeCenter.y_ << "), " << shapes_[i]->getArea();
    }
    out << "]";
}

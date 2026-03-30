#include "composite_shape.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

void CompositeShape::addShape(const std::shared_ptr<Shape>& shape)
{
    if (shape == nullptr)
    {
        throw std::invalid_argument("Shape pointer is null");
    }

    shapes_.push_back(shape);
}

double CompositeShape::getArea() const
{
    double totalArea = 0.0;

    for (const std::shared_ptr<Shape>& shape : shapes_)
    {
        totalArea += shape->getArea();
    }

    return totalArea;
}

Point CompositeShape::getCenter() const
{
    if (shapes_.empty())
    {
        throw std::invalid_argument("Composite shape is empty");
    }

    Bounds first = shapes_[0]->getBounds();
    double minX = first.minX;
    double maxX = first.maxX;
    double minY = first.minY;
    double maxY = first.maxY;

    for (const std::shared_ptr<Shape>& shape : shapes_)
    {
        Bounds b = shape->getBounds();
        if(b.minX < minX)
        {
            minX = b.minX;
        }

        if(b.maxX > maxX)
        {
            maxX = b.maxX;
        }

        if(b.minY < minY)
        {
            minY = b.minY;
        }

        if(b.maxY > maxY)
        {
            maxY = b.maxY;
        }
    }

    return { (minX + maxX) / 2.0, (minY + maxY) / 2.0 };
}

void CompositeShape::move(const Point& newCenter)
{
    if (shapes_.empty())
    {
        throw std::invalid_argument("Composite shape is empty");
    }

    Point oldCenter = getCenter();

    double dx = newCenter.x - oldCenter.x;
    double dy = newCenter.y - oldCenter.y;

    for (const std::shared_ptr<Shape>& shape : shapes_)
    {
        Point currentCenter = shape->getCenter();
        Point movedCenter;

        movedCenter.x = currentCenter.x + dx;
        movedCenter.y = currentCenter.y + dy;

        shape->move(movedCenter);
    }
}

void CompositeShape::scale(double ratio)
{
    if (ratio <= 0.0)
    {
        throw std::invalid_argument("Ratio must be positive");
    }

    if (shapes_.empty())
    {
        throw std::invalid_argument("Composite shape is empty");
    }

    Point compositeCenter = getCenter();

    for (const std::shared_ptr<Shape>& shape : shapes_)
    {
        Point shapeCenter = shape->getCenter();
        Point newCenter;

        newCenter.x = compositeCenter.x + (shapeCenter.x - compositeCenter.x) * ratio;
        newCenter.y = compositeCenter.y + (shapeCenter.y - compositeCenter.y) * ratio;

        shape->move(newCenter);
        shape->scale(ratio);
    }
}

std::string CompositeShape::getName() const
{
    return "COMPOSITE";
}

std::string CompositeShape::getDescription() const
{
    std::ostringstream oss;
    Point center = getCenter();
    oss << std::fixed << std::setprecision(2);
    oss << "[COMPOSITE, (" << center.x << ", " << center.y << "), " << getArea() << ":\n";

    for (size_t i = 0; i < shapes_.size(); i++)
    {
        Point c = shapes_[i]->getCenter();
        oss << "  " << shapes_[i]->getName()
            << ", (" << c.x << ", " << c.y << "), " << shapes_[i]->getArea();

        if (i + 1 < shapes_.size())
        {
            oss << ",";
        }

        oss << "\n";
    }
    oss << "]";
    return oss.str();
}

Bounds CompositeShape::getBounds() const
{
    if (shapes_.empty())
    {
        throw std::invalid_argument("Composite shape is empty");
    }

    auto first = shapes_[0]->getBounds();
    double minX = first.minX;
    double minY = first.minY;
    double maxX = first.maxX;
    double maxY = first.maxY;

    for (size_t i = 1; i < shapes_.size(); ++i)
    {
        auto b = shapes_[i]->getBounds();
        if (b.minX < minX) minX = b.minX;
        if (b.minY < minY) minY = b.minY;
        if (b.maxX > maxX) maxX = b.maxX;
        if (b.maxY > maxY) maxY = b.maxY;
    }

    return {minX, minY, maxX, maxY};
}
#include "compositeshape.h"
#include <algorithm>
#include <stdexcept>

CompositeShape::CompositeShape(std::vector<std::unique_ptr<Shape>>&& s) :
    shapes(std::move(s))
{
}

double CompositeShape::getArea() const
{
    double totalArea = 0;
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        totalArea += shapes[i]->getArea();
    }
    return totalArea;
}

void CompositeShape::add(std::unique_ptr<Shape> shape)
{
    shapes.push_back(std::move(shape));
}


Point CompositeShape::getCenter() const
{
    std::pair<Point, Point> box = Bounds();
    return Point((box.first.x + box.second.x) / 2.0, (box.first.y + box.second.y) / 2.0);
}

std::pair<Point, Point> CompositeShape::Bounds() const
{
    if (shapes.empty())
    {
        throw std::invalid_argument("CShape is empty\n");
    }
    double minX = shapes[0]->Bounds().first.x;
    double maxX = shapes[0]->Bounds().second.x;
    double minY = shapes[0]->Bounds().first.y;
    double maxY = shapes[0]->Bounds().second.y;
    for (size_t i = 1; i < shapes.size(); ++i)
    {
        minX = std::min(minX, shapes[i]->Bounds().first.x);
        minY = std::min(minY, shapes[i]->Bounds().first.y);
        maxX = std::max(maxX, shapes[i]->Bounds().second.x);
        maxY = std::max(maxY, shapes[i]->Bounds().second.y);
    }
    return std::make_pair(Point(minX, minY), Point(maxX, maxY));
}

std::string CompositeShape::getName() const
{
    return "COMPOSITE";
}

void CompositeShape::scale(double factor)
{
    Point commonCenter = getCenter();
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        double dx = (shapes[i]->getCenter().x - commonCenter.x) * (factor - 1);
        double dy = (shapes[i]->getCenter().y - commonCenter.y) * (factor - 1);
        shapes[i]->move(dx, dy);
        shapes[i]->scale(factor);
    }
}

void CompositeShape::move(double dx, double dy)
{
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        shapes[i]->move(dx, dy);
    }
}

void CompositeShape::print(std::ostream& os) const
{
    os << std::fixed << std::setprecision(2);
    os << "[" << getName() << ", " << getCenter() << ", " << getArea() << ":\n";
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        os << "  " << shapes[i]->getName() << ", " << shapes[i]->getCenter() << ", " << shapes[i]->getArea() << ",\n";
    }
    os << "]" << std::endl;
}

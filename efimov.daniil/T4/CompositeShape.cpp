#include "CompositeShape.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
    if (!shape)
    {
        throw std::invalid_argument("Nullptr!");
    }

    shapes.push_back(std::move(shape));
}

std::pair<Point, Point> CompositeShape::getFrame() const
{
    if (shapes.empty())
    {
        return { Point(0, 0), Point(0, 0) };
    }

    auto firstFrame = shapes[0]->getFrame();

    double minX = firstFrame.first.x;
    double minY = firstFrame.first.y;
    double maxX = firstFrame.second.x;
    double maxY = firstFrame.second.y;

    for (size_t i = 1; i < shapes.size(); ++i)
    {
        auto frame = shapes[i]->getFrame();

        if (frame.first.x < minX) minX = frame.first.x;
        if (frame.first.y < minY) minY = frame.first.y;
        if (frame.second.x > maxX) maxX = frame.second.x;
        if (frame.second.y > maxY) maxY = frame.second.y;
    }

    return { Point(minX, minY), Point(maxX, maxY) };
}

double CompositeShape::getArea() const
{
    double totalArea = 0.0;

    for (size_t i = 0; i < shapes.size(); ++i)
    {
        totalArea += shapes[i]->getArea();
    }

    return totalArea;
}

Point CompositeShape::getCenter() const
{
    auto frame = getFrame();

    double centerX = (frame.first.x + frame.second.x) / 2.0;
    double centerY = (frame.first.y + frame.second.y) / 2.0;

    return Point(centerX, centerY);
}


void CompositeShape::move(double dx, double dy)
{
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        shapes[i]->move(dx, dy);
    }
}

void CompositeShape::scale(double factor)
{
    if (factor <= 0.0)
    {
        throw std::invalid_argument("Scale factor must be positive");
    }

    if (shapes.empty())
    {
        return;
    }

    Point oldCompositeCenter = getCenter();

    std::vector<Point> oldCenters;
    oldCenters.reserve(shapes.size());

    for (size_t i = 0; i < shapes.size(); ++i)
    {
        oldCenters.push_back(shapes[i]->getCenter());
    }

    for (size_t i = 0; i < shapes.size(); ++i)
    {
        shapes[i]->scale(factor);
    }

    for (size_t i = 0; i < shapes.size(); ++i)
    {
        Point oldCenter = oldCenters[i];

        double dx = oldCenter.x - oldCompositeCenter.x;
        double dy = oldCenter.y - oldCompositeCenter.y;

        double newDx = dx * factor;
        double newDy = dy * factor;

        Point newCenter(oldCompositeCenter.x + newDx, oldCompositeCenter.y + newDy);

        Point currentCenter = shapes[i]->getCenter();

        shapes[i]->move(newCenter.x - currentCenter.x, newCenter.y - currentCenter.y);
    }


}

std::string CompositeShape::getName() const
{
    return "COMPOSITE";
}

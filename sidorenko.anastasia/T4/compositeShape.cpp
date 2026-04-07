#include "compositeShape.h"
#include <vector>
#include <algorithm>

void CompositeShape::addShape(std::unique_ptr<Shape> newShape)
{
    if (newShape)
    {
        shapes.push_back(std::move(newShape));
    }
}

std::pair<Point, Point> CompositeShape::getFrame() const
{
    if (shapes.empty())
    {
        return { Point(0, 0), Point(0, 0) };
    }

    std::pair<Point, Point> firstFrame = shapes[0]->getFrame();
    double minX = firstFrame.first.x;
    double minY = firstFrame.first.y;
    double maxX = firstFrame.second.x;
    double maxY = firstFrame.second.y;

    for (size_t i = 1; i < shapes.size(); ++i)
    {
        std::pair<Point, Point> frame = shapes[i]->getFrame();
        minX = std::min(minX, frame.first.x);
        minY = std::min(minY, frame.first.y);
        maxX = std::max(maxX, frame.second.x);
        maxY = std::max(maxY, frame.second.y);
    }
    return { Point(minX, minY), Point(maxX, maxY) };
}

double CompositeShape::getArea() const
{
    double area = 0.0;
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        area += shapes[i]->getArea();
    }
    return area;
}
Point CompositeShape::getCenter() const
{
    std::pair<Point, Point> boundingBox = getFrame();
    double centerX = (boundingBox.first.x + boundingBox.second.x) / 2.0;
    double centerY = (boundingBox.first.y + boundingBox.second.y) / 2.0;
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
    Point compositeCenter = getCenter();
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        Point shapeCenter = shapes[i]->getCenter();
        double dx = shapeCenter.x - compositeCenter.x;
        double dy = shapeCenter.y - compositeCenter.y;
        double newDx = dx * factor;
        double newDy = dy * factor;
        Point newShapeCenter = Point(newDx + compositeCenter.x, newDy + compositeCenter.y);
        shapes[i]->move(newShapeCenter.x - shapeCenter.x, newShapeCenter.y - shapeCenter.y);
        shapes[i]->scale(factor);
    }
}
std::string CompositeShape::getName() const
{
    return "COMPOSITE";
}
const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const
{
    return shapes;
}


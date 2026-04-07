#include "Composite_shape.h"
void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{ shapes.push_back(std::move(shape)); }
double CompositeShape::getArea()
{
    double total = 0;
    for (size_t i = 0; i < shapes.size(); i++)
    {
        total += shapes[i]->getArea();
    }
    return total;
}
Point CompositeShape::getCenter()
{
    if (shapes.empty())
    {
        return { 0, 0 };
    }
    double min_x = shapes[0]->getX_min();
    double min_y = shapes[0]->getY_min();
    double max_x = shapes[0]->getX_max();
    double max_y = shapes[0]->getY_max();

    for (size_t i = 1; i < shapes.size(); i++)
    {
        if (shapes[i]->getX_max() > max_x)
        {
            max_x = shapes[i]->getX_max();
        }
        if (shapes[i]->getX_min() < min_x)
        {
            min_x = shapes[i]->getX_min();
        }
        if (shapes[i]->getY_max() > max_y)
        {
            max_y = shapes[i]->getY_max();
        }
        if (shapes[i]->getY_min() < min_y)
        {
            min_y = shapes[i]->getY_min();
        }
    }
    return { (max_x + min_x) / 2 , (max_y + min_y) / 2 };
}
void CompositeShape::move(double x_, double y_)
{
    for (size_t i = 0; i < shapes.size(); i++)
    {
        shapes[i]->move(x_, y_);
    }
}
void CompositeShape::scale(double k)
{
    Point center = this->getCenter();
    for (size_t i = 0; i < shapes.size(); i++)
    {
        double dx = shapes[i]->getCenter().x - center.x;
        double dy = shapes[i]->getCenter().y - center.y;
        dx *= k; dy *= k;
        double new_center_x = center.x + dx;
        double new_center_y = center.y + dy;
        double move_x = new_center_x - shapes[i]->getCenter().x;
        double move_y = new_center_y - shapes[i]->getCenter().y;
        shapes[i]->move(move_x, move_y);
        shapes[i]->scale(k);
    }
}
std::string CompositeShape::getName() { return "COMPOSITE"; }
double CompositeShape::getX_min()
{
    if (shapes.empty()) return 0;
    double min_x = shapes[0]->getX_min();
    for (size_t i = 1; i < shapes.size(); i++)
    {
        if (shapes[i]->getX_min() < min_x)
            min_x = shapes[i]->getX_min();
    }
    return min_x;
}

double CompositeShape::getX_max()
{
    if (shapes.empty()) return 0;
    double max_x = shapes[0]->getX_max();
    for (size_t i = 1; i < shapes.size(); i++)
    {
        if (shapes[i]->getX_max() > max_x)
            max_x = shapes[i]->getX_max();
    }
    return max_x;
}

double CompositeShape::getY_min()
{
    if (shapes.empty()) return 0;
    double min_y = shapes[0]->getY_min();
    for (size_t i = 1; i < shapes.size(); i++)
    {
        if (shapes[i]->getY_min() < min_y)
            min_y = shapes[i]->getY_min();
    }
    return min_y;
}

double CompositeShape::getY_max()
{
    if (shapes.empty()) return 0;
    double max_y = shapes[0]->getY_max();
    for (size_t i = 1; i < shapes.size(); i++)
    {
        if (shapes[i]->getY_max() > max_y)
            max_y = shapes[i]->getY_max();
    }
    return max_y;
}
void CompositeShape::print()
{
    std::cout << "[" << getName() << ", (" << getCenter().x << ", " << getCenter().y << "), " << getArea() << ":\n";
    for (size_t i = 0; i < shapes.size(); i++)
    {
        std::cout << "  " << shapes[i]->getName() << ", (" << shapes[i]->getCenter().x
        << ", " << shapes[i]->getCenter().y << "), " << shapes[i]->getArea() << ";\n";
    }
    std::cout << "]\n";
}

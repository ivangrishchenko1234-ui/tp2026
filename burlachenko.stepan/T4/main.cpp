#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include "composite_shape.h"
#include "rectangle.h"
#include "ring.h"
#include "square.h"

void printShape(const Shape& shape)
{
    Point center = shape.getCenter();

    std::cout << "[" << shape.getName() << ", ("
    << std::fixed << std::setprecision(2) << center.x
    << ", " << center.y << "), "
    << shape.getArea() << "]\n";
}

int main()
{
    std::vector<std::shared_ptr<Shape>> shapes;

    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Point{0.0, 0.0}, Point{4.0, 2.0});

    std::shared_ptr<Shape> rectangle2 = std::make_shared<Rectangle>(Point{1.0, 1.0}, Point{3.0, 5.0});

    std::shared_ptr<Shape> ring1 = std::make_shared<Ring>(Point{2.0, 2.0}, 1.0, 3.0);

    std::shared_ptr<Shape> square1 = std::make_shared<Square>(Point{0.0, 0.0}, 2.0);

    std::shared_ptr<CompositeShape> composite = std::make_shared<CompositeShape>();
    composite->addShape(rectangle1);
    composite->addShape(ring1);

    shapes.push_back(rectangle1);
    shapes.push_back(rectangle2);
    shapes.push_back(ring1);
    shapes.push_back(square1);
    shapes.push_back(composite);

    std::cout << "Before scaling:\n";
    for (const std::shared_ptr<Shape>& shape : shapes)
    {
        printShape(*shape);
    }

    for (const std::shared_ptr<Shape>& shape : shapes)
    {
        shape->scale(2.0);
    }

    std::cout << "After scaling:\n";
    for (const std::shared_ptr<Shape>& shape : shapes)
    {
        printShape(*shape);
    }


    return 0;
}

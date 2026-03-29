#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <cstring>
#include "rectangle.h"
#include "ellipse.h"
#include "rectTrapezoid.h"
#include "compositeShape.h"

void printShape(const Shape* shape)
{
    std::cout << std::fixed << std::setprecision(2);
    Point center = shape->getCenter();
    std::cout << "[" << shape->getName() << ",(" << center.x_ << ", "
              << center.y_ << "), " << shape->getArea() << "]" << std::endl;
}

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;

    auto rect1 = std::make_unique<Rectangle>(0.0, 0.0, 4.0, 3.0);
    shapes.push_back(std::move(rect1));

    auto ellipse1 = std::make_unique<Ellipse>(5.0, 5.0, 2.0, 3.0);
    shapes.push_back(std::move(ellipse1));

    auto trapezoid1 = std::make_unique<RectTrapezoid>(10.0, 0.0, 4.0, 2.0, 3.0);
    shapes.push_back(std::move(trapezoid1));

    auto rect2 = std::make_unique<Rectangle>(1.0, 1.0, 3.0, 4.0);
    shapes.push_back(std::move(rect2));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(0.0, 0.0, 2.0, 2.0));
    composite->addShape(std::make_unique<Ellipse>(3.0, 1.0, 1.0, 1.0));
    composite->addShape(
        std::make_unique<RectTrapezoid>(5.0, 0.0, 2.0, 1.0, 1.5));
    shapes.push_back(std::move(composite));

    std::cout << "Before scaling:" << std::endl;
    for (const auto& shape : shapes)
    {
        if (std::strcmp(shape->getName(), "COMPOSITE") == 0)
        {
            CompositeShape* comp =
                dynamic_cast<CompositeShape*>(shape.get());
            if (comp != nullptr)
            {
                comp->printDetails(std::cout);
                std::cout << std::endl;
            }
        }
        else
        {
            printShape(shape.get());
        }
    }

    std::cout << std::endl << "After scaling (x2):" << std::endl;
    for (auto& shape : shapes)
    {
        shape->scale(2.0);
    }

    for (const auto& shape : shapes)
    {
        if (std::strcmp(shape->getName(), "COMPOSITE") == 0)
        {
            CompositeShape* comp =
                dynamic_cast<CompositeShape*>(shape.get());
            if (comp != nullptr)
            {
                comp->printDetails(std::cout);
                std::cout << std::endl;
            }
        }
        else
        {
            printShape(shape.get());
        }
    }

    return 0;
}

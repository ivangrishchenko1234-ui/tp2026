#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "Rectangle.h"
#include "Circle.h"
#include "RectangularTrapezoid.h"
#include "CompositeShape.h"

void printInfo(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    std::cout << std::fixed << std::setprecision(2);

    for (const auto& shape : shapes)
    {

        const CompositeShape* composite = dynamic_cast<const CompositeShape*>(shape.get());

        if (composite)
        {
            std::cout << "[" << composite->getName() << ", ("
                << composite->getCenter().x << ", " << composite->getCenter().y << "), "
                << composite->getArea() << ":\n";

            const auto& inner = composite->getShapes();
            for (size_t j = 0; j < inner.size(); ++j)
            {
                std::cout << "  " << inner[j]->getName() << ", ("
                    << inner[j]->getCenter().x << ", " << inner[j]->getCenter().y << "), "
                    << inner[j]->getArea();
                if (j < inner.size() - 1) std::cout << ",";
                std::cout << "\n";
            }
            std::cout << "]\n";
        }
        else
        {
            std::cout << "[" << shape->getName() << ", ("
                << shape->getCenter().x << ", " << shape->getCenter().y << "), "
                << shape->getArea() << "]\n";
        }
    }
}

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
    shapes.push_back(std::make_unique<Circle>(Point(5, 5), 2));
    shapes.push_back(std::make_unique<RectangularTrapezoid>(Point(-2, -1), 4, 2, 3));
    shapes.push_back(std::make_unique<RectangularTrapezoid>(Point(-3, 2), 3, 1, 2));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point(2, -2), Point(5, 1)));
    composite->addShape(std::make_unique<Circle>(Point(-1, 0), 1.5));
    composite->addShape(std::make_unique<RectangularTrapezoid>(Point(6, 1), 2, 1, 2));

    shapes.push_back(std::move(composite));

    std::cout << "BEFORE SCALE:\n";
    printInfo(shapes);

    for (auto& shape : shapes)
    {
        shape->scale(2.0);
    }

    std::cout << "\nAFTER SCALE:\n";
    printInfo(shapes);

    return 0;
}

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>
#include "shape.h"
#include "point.h"
#include "rectangle.h"
#include "circle.h"
#include "rightTrapezoid.h"
#include "compositeShape.h"
void printInfo(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    std::cout << std::fixed << std::setprecision(2);

    for (size_t i = 0; i < shapes.size(); ++i)
    {
        double cX = shapes[i]->getCenter().x;
        double cY = shapes[i]->getCenter().y;
        const CompositeShape* composite = dynamic_cast<const CompositeShape*>(shapes[i].get());
        if (composite)
        {
            std::cout << "[" << composite->getName() << ", (" << cX << ", " << cY << "), "
                << composite->getArea() << ":\n";

            const std::vector<std::unique_ptr<Shape>>& innerShapes = composite->getShapes();
            if (!innerShapes.empty())
            {
                for (size_t j = 0; j < innerShapes.size() - 1; ++j)
                {
                    double icX = innerShapes[j]->getCenter().x;
                    double icY = innerShapes[j]->getCenter().y;
                    std::cout << "  " << innerShapes[j]->getName() << ", ("
                        << icX << ", " << icY << "), "
                        << innerShapes[j]->getArea() << "," << "\n";
                }
                std::cout << "  " << innerShapes[innerShapes.size() - 1]->getName() << ", ("
                    << innerShapes[innerShapes.size() - 1]->getCenter().x << ", " <<
                    innerShapes[innerShapes.size() - 1]->getCenter().y << "), "
                    << innerShapes[innerShapes.size() - 1]->getArea() << "\n";
                std::cout << "]\n";
            }
        }
        else
        {
            std::cout << "[" << shapes[i]->getName() << ", (" << cX << ", " << cY << "), "
                << shapes[i]->getArea() << "]\n";
        }
    }
}
int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(2, 3)));
    shapes.push_back(std::make_unique<Circle>(Point(5, 5), 2));
    shapes.push_back(std::make_unique<RightTrapezoid>(Point(-3, -2), 3, 2, 2));
    shapes.push_back(std::make_unique<RightTrapezoid>(Point(-4, 3), 2, 4, 2));
    std::unique_ptr<CompositeShape> composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point(3, -2), Point(7, 0)));
    composite->addShape(std::make_unique<Circle>(Point(-1, 1), 1));
    composite->addShape(std::make_unique<RightTrapezoid>(Point(9, 3), 2, 1, 3));
    shapes.push_back(std::move(composite));
    printInfo(shapes);
    double factor = 0.0;
    if (!(std::cin >> factor))
    {
        return 0;
    }
    if (factor <= 0.0)
    {
        return 0;
    }
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        shapes[i]->scale(factor);
    }
    printInfo(shapes);
    return 0;
}


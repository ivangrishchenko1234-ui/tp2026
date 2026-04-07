#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <memory>
#include "CompositeShape.h"

void printInfo(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    for (size_t i = 0; i < shapes.size(); i++)
    {
        if (shapes[i]->getName() != "COMPOSITE")
        {
            std::cout << "[" << shapes[i]->getName() << ", (" << shapes[i]->getCenter().x
                << ", " << shapes[i]->getCenter().y << "), " << shapes[i]->getArea() << "]\n";
        }
        else
        {
            std::cout << "[" << shapes[i]->getName() << ", (" << shapes[i]->getCenter().x
                << ", " << shapes[i]->getCenter().y << "), " << shapes[i]->getArea() << ":\n";
            CompositeShape* composite = dynamic_cast<CompositeShape*>(shapes[i].get());
            for (size_t j = 0; j < composite->membersAccess().size(); j++)
            {
                std::cout << '\t' << composite->membersAccess()[j]->getName() << ", " << "("
                    << composite->membersAccess()[j]->getCenter().x << ", "
                    << composite->membersAccess()[j]->getCenter().y << "), "
                    << composite->membersAccess()[j]->getArea() << ",\n";
            }
            std::cout << "]\n";
        }
    }
}

int main()
{
    std::cout << std::fixed << std::setprecision(2);
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(Point(-2.0, 4.0), Point(1.0, 8.0)));
    shapes.push_back(std::make_unique<Ellipse>(Point(1.0, 2.0), 10.0, 6.0));
    shapes.push_back(std::make_unique<Square>(Point(0.0, 0.0), 7.0));

    std::unique_ptr<Shape> lanino = std::make_unique<Rectangle>(Point(-3.0, -3.0), Point(0.0, 5.0));
    std::unique_ptr<Shape> rouxls = std::make_unique<Rectangle>(Point(5.0, -2.0), Point(7.0, 1.0));
    std::unique_ptr<Shape> elnina = std::make_unique<Ellipse>(Point(3.0, 3.0), 8.0, 6.0);
    auto trifecta = std::make_unique<CompositeShape>();

    trifecta->putInComposite(std::move(lanino));
    trifecta->putInComposite(std::move(rouxls));
    trifecta->putInComposite(std::move(elnina));

    shapes.push_back(std::move(trifecta));
    printInfo(shapes);
    for (size_t i = 0; i < shapes.size(); i++)
    {
        shapes[i]->scale(2.0);
    }
    std::cout << "\n ====================================================================== \n\n";
    printInfo(shapes);
    return 0;
}

#include <iostream>
#include <iomanip>
#include "Rectangle.h"
#include "Square.h"
#include "Ring.h"
#include "Composite_shape.h"
void printInfo(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    std::cout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        shapes[i]->print();
        std::cout << "\n";
    }
}
int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(Point{ 1,1 }, Point{ 4,3 }));
    shapes.push_back(std::make_unique<Square>(Point{ 2,2 }, 3));
    shapes.push_back(std::make_unique<Ring>(Point{ 0,0 }, 5, 3));
    shapes.push_back(std::make_unique<Rectangle>(Point{ 0,0 }, Point{ 2,2 }));
    shapes.push_back(std::make_unique<Square>(Point{ 3,3 }, 2));
    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point{ 10, 10 }, Point{ 14, 13 }));
    composite->addShape(std::make_unique<Ring>(Point{ 12, 12 }, 1, 0.5));
    shapes.push_back(std::move(composite));
    printInfo(shapes);
    double k = 2.0;
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        shapes[i]->scale(k);
    }
    printInfo(shapes);
    return 0;
}

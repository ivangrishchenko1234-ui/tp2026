#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>

#include "Rectangle.h"
#include "Ellipse.h"
#include "Rectangular_trapezoid.h"
#include "Composite_shape.h"
#include "Point.h"
#include "Shape.h"

void printInfo(const std::vector<std::unique_ptr<Shape>>& shapes) {
    std::cout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < shapes.size(); ++i) {
        const CompositeShape* composite = dynamic_cast<const CompositeShape*>(shapes[i].get());
        if (composite) {
            composite->print(std::cout);
        }
        else {
            Point center = shapes[i]->getCenter();
            std::cout << "[" << shapes[i]->getName() << ", (";
            std::cout << center.x << ", " << center.y << "), " << shapes[i]->getArea() << "]\n";
        }
    }
    std::cout << "\n";
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
    shapes.push_back(std::make_unique<Ellipse>(Point(5, 5), 2, 1.5));
    shapes.push_back(std::make_unique<Rectangular_trapezoid>(Point(1, 1), 6, 4, 2));
    shapes.push_back(std::make_unique<Rectangle>(Point(2, 2), Point(5, 4)));
    shapes.push_back(std::make_unique<Ellipse>(Point(8, 3), 1.5, 1));

    auto composite = std::make_unique<CompositeShape>();

    composite->addShape(std::make_unique<Rectangle>(Point(10, 10), Point(14, 13)));
    composite->addShape(std::make_unique<Ellipse>(Point(12, 12), 1, 0.5));
    shapes.push_back(std::move(composite));

    std::cout << "======= before scale ======\n";
    printInfo(shapes);
    double factor = 0.0;
    if (!(std::cin >> factor))
    {
        std::cerr << "Error with std::cin\n";
        return 1;
    }
    if (factor <= 0.0)
    {
        std::cerr << "Error factor must be positive\n";
        return 1;
    }
    for (size_t i = 0; i < shapes.size(); ++i) {
        shapes[i]->scale(factor);
    }

    std::cout << "======= after scale ======\n";
    printInfo(shapes);
    return 0;
}

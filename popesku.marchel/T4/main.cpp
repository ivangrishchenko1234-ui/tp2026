#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>

#include "Rectangle.h"
#include "Ring.h"
#include "IsoscelesTrapezoid.h"
#include "Composite_Shape.h"

int main() {
    std::cout << std::fixed << std::setprecision(2);

    std::vector<std::unique_ptr<Shape> > shapes;
    shapes.push_back(std::make_unique<Rectangle>(Point(1, 1), Point(4, 3)));
    shapes.push_back(std::make_unique<Ring>(Point(6, 6), 4, 2));
    shapes.push_back(std::make_unique<IsoscelesTrapezoid>(Point(0, 0), 6, 3, 4));

    std::cout << "Figures: \n";
    for (size_t i = 0; i < shapes.size(); i++) {
        shapes[i]->print();
    }
    std::cout << "\n\n";

    CompositeShape composite;
    composite.addShape(std::make_unique<Rectangle>(Point(2, 4), Point(6, 5)));
    composite.addShape(std::make_unique<Ring>(Point(7, 8), 5, 2));
    composite.addShape(std::make_unique<IsoscelesTrapezoid>(Point(4, 4), 6, 3, 4));
    composite.addShape(std::make_unique<Rectangle>(Point(3, 1), Point(5, 6)));
    composite.addShape(std::make_unique<Ring>(Point(1, 1), 3, 1));

    std::cout << "Before scaling:\n";
    composite.print();

    composite.scale(2);

    std::cout << "After scaling:\n";
    composite.print();
    return 0;
}

#include <iostream>
#include <ostream>
#include <vector>
#include <memory>
#include <iomanip>

#include "shape.h"
#include "rectangle.h"
#include "ellipse.h"
#include "point.h"
#include "rectangular_trapezoid.h"
#include "composite_shape.h"

void printInfo(const std::vector<std::unique_ptr<Shape>>& shapes, std::ostream& stream) {
    std::cout << std::fixed << std::setprecision(2);

    for (const auto& shape : shapes) {
        if (shape) {
            shape->print(stream);
            std::cout << "\n";
        }
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(2, 3)));
    shapes.push_back(std::make_unique<Ellipse>(Point(5, 5), 2.0, 1.5));
    shapes.push_back(std::make_unique<Rectangle>(Point(-1, -2), Point(7, 8)));
    shapes.push_back(std::make_unique<RectangularTrapezoid>(Point(1, 1), 3.0, 1.0, 2.0));

    auto compositePtr = std::make_unique<CompositeShape>();
    compositePtr->addShape(std::make_unique<Rectangle>(Point(10, 10), Point(12, 13)));
    compositePtr->addShape(std::make_unique<Ellipse>(Point(15, 15), 3.0, 2.0));
    shapes.push_back(std::move(compositePtr));

    double factor;
    std::cout << "factor: ";

    if (!(std::cin >> factor)) {
        if (std::cin.eof()) {
            factor = 1.0;
        } else {
            std::cerr << "ERROR: No input provided!\n";
            return 1;
        }
    }

    if (factor <= 0.0) {
        std::cerr << "ERROR: Factor must be positive" << "\n";
        return 1;
    }


    std::cout << "\n--- before ---\n";
    printInfo(shapes, std::cout);

    for (const auto& shape_ptr : shapes) {
        if (shape_ptr) {
            shape_ptr->scale(factor);
        }
    }

    std::cout << "\n--- after ---\n";
    printInfo(shapes, std::cout);

    return 0;
}

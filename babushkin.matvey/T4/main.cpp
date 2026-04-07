#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include "point.h"
#include "rectangle.h"
#include "trapezoid.h"
#include "composite_shape.h"

void printInfo(const std::vector<std::unique_ptr<Shape>>& shapes) {
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& s : shapes) {
        Point c = s->getCenter();
        std::cout << "[" << s->getName() << ", ("
                  << c.x << ", " << c.y << "), "
                  << s->getArea() << "]\n";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    try {
        shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
        shapes.push_back(std::make_unique<Rectangle>(Point(5, 5), Point(7, 8)));
        shapes.push_back(std::make_unique<Trapezoid>(Point(1, 1), 6, 4, 3));
        shapes.push_back(std::make_unique<Trapezoid>(Point(10, 2), 5, 3, 2));

        auto composite = std::make_unique<CompositeShape>();
        composite->addShape(std::make_unique<Rectangle>(Point(2, 2), Point(5, 4)));
        composite->addShape(std::make_unique<Trapezoid>(Point(3, 1), 4, 2, 2));
        shapes.push_back(std::move(composite));

        shapes.push_back(std::make_unique<Rectangle>(Point(-2, -2), Point(0, 0)));
    } catch (const std::exception& e) {
        std::cerr << "Error creating shapes: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "=== BEFORE SCALE ===\n";
    printInfo(shapes);

    for (auto& s : shapes) {
        s->scale(2.0);
    }

    std::cout << "=== AFTER SCALE (x2) ===\n";
    printInfo(shapes);

    return 0;
}

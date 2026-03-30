#include "rectangle.h"
#include "circle.h"
#include "rhombus.h"
#include "compositeshape.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

void printInfo(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (auto& shape : shapes) {
        shape->print();
    }
}

int main() {
    try {
        std::vector<std::unique_ptr<Shape>> shapes;
        shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
        shapes.push_back(std::make_unique<Circle>(Point(5, 5), 2));
        shapes.push_back(std::make_unique<Rhombus>(Point(-2, 3), 4, 6));
        auto composite = std::make_unique<CompositeShape>();
        auto rect1 = std::make_unique<Rectangle>(Point(1, 1), Point(3, 4));
        auto rect2 = std::make_unique<Rectangle>(Point(4, 2), Point(6, 5));
        auto circle1 = std::make_unique<Circle>(Point(2, 3), 1.5);
        composite->addShape(std::move(rect1));
        composite->addShape(std::move(rect2));
        composite->addShape(std::move(circle1));
        shapes.push_back(std::move(composite));
        std::cout << "Before scale\n";
        printInfo(shapes);
        double factor;
        std::cin >> factor;
        if (std::cin.fail()) {
            std::cerr << "Error: Invalid scale factor input\n";
            return 0;
        }
        if (factor <= 0.0)
        {
            throw std::invalid_argument("factor must be positive");
        }
        for (auto& shape : shapes) {
            shape->scale(factor);
        }
        std::cout << "After scale\n";
        printInfo(shapes);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

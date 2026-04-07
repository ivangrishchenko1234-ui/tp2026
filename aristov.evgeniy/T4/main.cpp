#include <iostream>
#include <vector>
#include <memory>

#include "point.h"
#include "shape.h"
#include "rectangle.h"
#include "ring.h"
#include "right_trapezoid.h"
#include "composite_shape.h"

int main() {
    try {
        std::vector<std::unique_ptr<Shape>> shapes;

        shapes.push_back(std::make_unique<Rectangle>(Point{0.0, 0.0}, Point{4.0, 2.0}));
        shapes.push_back(std::make_unique<Ring>(Point{5.0, 5.0}, 3.0, 1.0));
        shapes.push_back(std::make_unique<RightTrapezoid>(Point{-2.0, -2.0}, 4.0, 2.0, 3.0));
        shapes.push_back(std::make_unique<Rectangle>(Point{10.0, 10.0}, Point{12.0, 12.0}));

        auto composite = std::make_unique<CompositeShape>();
        composite->addShape(std::make_unique<Rectangle>(Point{1.0, 1.0}, Point{3.0, 3.0}));
        composite->addShape(std::make_unique<Ring>(Point{2.0, 2.0}, 2.0, 0.5));
        shapes.push_back(std::move(composite));

        std::cout << "--- Figures BEFORE scaling ---\n";
        for (const auto& shape : shapes) {
            std::cout << shape->toString() << "\n";
        }

        double factor = 0.0;
        if (!(std::cin >> factor)) {
            std::cerr << "Error: no scale factor provided\n";
            return 1;
        }
        if (factor <= 0.0) {
            std::cerr << "Error: scale factor must be positive\n";
            return 1;
        }

        for (auto& shape : shapes) {
            shape->scale(factor);
        }

        std::cout << "\n--- Figures AFTER scaling (x" << factor << ") ---\n";
        for (const auto& shape : shapes) {
            std::cout << shape->toString() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

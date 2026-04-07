#include "rectangle.hpp"
#include "right_trapezoid.hpp"
#include "composite_shape.hpp"
#include "circle.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>

void printShapes(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (size_t i = 0; i < shapes.size(); ++i) {
        if (shapes[i]->getName() == "COMPOSITE") {
            const CompositeShape* composite = dynamic_cast<const CompositeShape*>(shapes[i].get());
            if (composite) {
                std::cout << *composite << std::endl;
            }
        }
        else {
            std::cout << *shapes[i] << std::endl;
        }
    }
}

int main() {
    try {
        std::vector<std::unique_ptr<Shape>> shapes;
        shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
        shapes.push_back(std::make_unique<RightTrapezoid>(Point(2, 1), 6, 4, 3));
        shapes.push_back(std::make_unique<Circle>(Point(5, 5), 2));
        shapes.push_back(std::make_unique<Rectangle>(Point(10, 2), Point(13, 7)));

        auto composite = std::make_unique<CompositeShape>();
        composite->addShape<Rectangle>(Point(0, 0), Point(2, 2));
        composite->addShape<Circle>(Point(3, 3), 1);
        composite->addShape<RightTrapezoid>(Point(1, 1), 3, 2, 2);
        shapes.push_back(std::move(composite));

        std::cout << "Before scaling:";
        printShapes(shapes);

        for (auto& shape : shapes) {
            shape->scale(2.0);
        }
        std::cout << "\nAfter scaling:";
        printShapes(shapes);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

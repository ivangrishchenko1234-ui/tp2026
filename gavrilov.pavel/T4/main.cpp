#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "rectangle.h"
#include "ring.h"
#include "square.h"
#include "composite_shape.h"

void printShapeInfo(const Shape& shape) {
    Point center = shape.getCenter();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[" << shape.getName()
        << ", (" << center.x << ", " << center.y << "), "
        << shape.getArea() << "]\n";
}

int main() {
    std::cout << "Shapes descripton withot scaling\n";

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== GEOMETRIC SHAPES ===\n\n";

    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
    shapes.push_back(std::make_unique<Ring>(Point(5, 5), 5.0, 2.0));
    shapes.push_back(std::make_unique<Square>(Point(2, 2), 3.0));
    shapes.push_back(std::make_unique<Rectangle>(Point(-2, -1), Point(1, 2)));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point(10, 10), Point(13, 12)));
    composite->addShape(std::make_unique<Square>(Point(15, 10), 2.0));
    composite->addShape(std::make_unique<Ring>(Point(12, 15), 2.0, 1.0));
    shapes.push_back(std::move(composite));

    std::cout << "BEFORE SCALING BY 2:\n";
    std::cout << "====================\n";
    for (const auto& shape : shapes) {
        if (shape->getName() == "COMPOSITE") {
            const CompositeShape* comp = dynamic_cast<const CompositeShape*>(shape.get());
            if (comp) {
                comp->printInfo();
            }
        } else {
            printShapeInfo(*shape);
        }
    }

    std::cout << "\nSCALING BY 2...\n\n";
    for (auto& shape : shapes) {
        shape->scale(2.0);
    }

    std::cout << "AFTER SCALING BY 2:\n";
    std::cout << "===================\n";
    for (const auto& shape : shapes) {
        if (shape->getName() == "COMPOSITE") {
            const CompositeShape* comp = dynamic_cast<const CompositeShape*>(shape.get());
            if (comp) {
                comp->printInfo();
            }
        } else {
            printShapeInfo(*shape);
        }
    }

    return 0;
}

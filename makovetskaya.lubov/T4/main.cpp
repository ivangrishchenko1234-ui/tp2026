#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <stdexcept>
#include "Rectangle.h"
#include "Ring.h"
#include "Rhombus.h"
#include "Compositeshape.h"

void printSimpleShapeInfo(const std::shared_ptr<Shape>& shape) {
    Point center = shape->getCenter();
    std::cout << shape->getName() << ", (" << std::fixed << std::setprecision(2) << center.x << ", " << center.y << "), " << shape->getArea();
}

void printShapeInfo(const std::shared_ptr<Shape>& shape, int indentLevel = 0) {
    std::string indent(indentLevel * 2, ' ');

    auto composite = std::dynamic_pointer_cast<CompositeShape>(shape);
    if (composite) {
        Point center = composite->getCenter();
        std::cout << indent << "[COMPOSITE, (" << std::fixed << std::setprecision(2) << center.x << ", " << center.y << "), " << composite->getArea() << ":\n";

        const auto& shapes = composite->getShapes();
        for (size_t i = 0; i < shapes.size(); ++i) {
            std::cout << indent << "  ";
            printSimpleShapeInfo(shapes[i]);
            if (i < shapes.size() - 1) {
                std::cout << ",";
            }
            std::cout << "\n";
        }
        std::cout << indent << "]";
    }
    else {
        std::cout << indent << "[";
        printSimpleShapeInfo(shape);
        std::cout << "]";
    }
}

int main() {
    std::vector<std::shared_ptr<Shape>> shapes;

    shapes.push_back(std::make_shared<Rectangle>(Point(0, 0), Point(4, 3)));
    shapes.push_back(std::make_shared<Ring>(Point(2, 2), 5, 3));
    shapes.push_back(std::make_shared<Rhombus>(Point(-1, 1), 6, 4));
    shapes.push_back(std::make_shared<Ring>(Point(-2, -2), 3, 1.5));

    auto composite = std::make_shared<CompositeShape>();
    composite->addShape(std::make_shared<Rectangle>(Point(2, 2), Point(4, 4)));
    composite->addShape(std::make_shared<Ring>(Point(4, 4), 2, 1));
    composite->addShape(std::make_shared<Rhombus>(Point(5, 3), 4, 3));
    shapes.push_back(composite);

    for (const auto& shape : shapes) {
        printShapeInfo(shape);
        std::cout << "\n";
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

    for (const auto& shape : shapes) {
        printShapeInfo(shape);
        std::cout << "\n";
    }

    return 0;
}

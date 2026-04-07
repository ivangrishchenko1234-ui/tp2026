#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include "Rectangle.h"
#include "Square.h"
#include "Ellipse.h"
#include "CompositeShape.h"

void printShapeInfo(const Shape& shape) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[" << shape.getName() << ", " << shape.getCenter() << ", " << shape.getArea() << "]";
}

void printCompositeInfo(const CompositeShape& composite) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[COMPOSITE, " << composite.getCenter() << ", " << composite.getArea() << ":" << std::endl;
    const auto& shapes = composite.getShapes();
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << "  ";
        printShapeInfo(*shapes[i]);
        if (i < shapes.size() - 1) {
            std::cout << ",";
        }
        std::cout << std::endl;
    }
    std::cout << "]" << std::endl;
}

void printAllShapes(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (size_t i = 0; i < shapes.size(); ++i) {
        const auto& shape = shapes[i];
        if (shape->getName() == "COMPOSITE") {
            const CompositeShape* composite = dynamic_cast<const CompositeShape*>(shape.get());
            if (composite) {
                printCompositeInfo(*composite);
            }
        } else {
            printShapeInfo(*shape);
            std::cout << std::endl;
        }
    }
}

int main() {
    try {
        std::cout << std::fixed << std::setprecision(2);

        std::vector<std::unique_ptr<Shape>> shapes;

        shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
        shapes.push_back(std::make_unique<Square>(Point(5, 1), 2));
        shapes.push_back(std::make_unique<Ellipse>(Point(2, 5), 3, 2));
        shapes.push_back(std::make_unique<Rectangle>(Point(-2, -1), Point(1, 2)));

        auto composite = std::make_unique<CompositeShape>();
        composite->addShape(std::make_unique<Rectangle>(Point(1, 1), Point(3, 4)));
        composite->addShape(std::make_unique<Ellipse>(Point(5, 3), 1.5, 1));
        composite->addShape(std::make_unique<Square>(Point(2, 2), 1.5));
        shapes.push_back(std::move(composite));

        std::cout << "Creating shapes..." << std::endl;
        std::cout << "Total shapes: " << shapes.size() << std::endl;
        std::cout << "======================================" << std::endl;

        std::cout << "\nBEFORE SCALING:" << std::endl;
        std::cout << "======================================" << std::endl;
        printAllShapes(shapes);

        double factor;
        std::cout << "\nEnter scale factor: ";
        if (!(std::cin >> factor)) {
            std::cerr << "ERROR: Failed to read scale factor" << std::endl;
            return 1;
        }

        if (factor <= 0.0) {
            std::cerr << "ERROR: Scale factor must be positive" << std::endl;
            return 1;
        }

        std::cout << "\nScaling all shapes by factor " << factor << "..." << std::endl;
        for (auto& shape : shapes) {
            shape->scale(factor);
        }

        std::cout << "\nAFTER SCALING:" << std::endl;
        std::cout << "======================================" << std::endl;
        printAllShapes(shapes);

    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

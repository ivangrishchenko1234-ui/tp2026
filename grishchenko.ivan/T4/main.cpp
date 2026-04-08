#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "rectangle.h"
#include "ring.h"
#include "isosceles_trapezoid.h"
#include "composite_shape.h"

void printShapeInfo(const Shape& shape) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[" << shape.getName() << ", ("
        << shape.getCenter().x << ", " << shape.getCenter().y << "), "
        << shape.getArea();

    const CompositeShape* composite = dynamic_cast<const CompositeShape*>(&shape);
    if (composite) {
        std::cout << ":" << std::endl;
        const auto& shapes = composite->getShapes();
        for (size_t i = 0; i < shapes.size(); ++i) {
            std::cout << "  " << shapes[i]->getName() << ", ("
                << shapes[i]->getCenter().x << ", " << shapes[i]->getCenter().y << "), "
                << shapes[i]->getArea();
            if (i < shapes.size() - 1) {
                std::cout << ",";
            }
            std::cout << std::endl;
        }
        std::cout << "]";
    }
    else {
        std::cout << "]";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point{ 0.0, 0.0 }, Point{ 4.0, 3.0 }));

    shapes.push_back(std::make_unique<Ring>(Point{ 5.0, 5.0 }, 3.0, 1.0));

    shapes.push_back(std::make_unique<IsoscelesTrapezoid>(Point{ 10.0, 0.0 }, 6.0, 4.0, 3.0));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point{ 0.0, 0.0 }, Point{ 2.0, 2.0 }));
    composite->addShape(std::make_unique<Ring>(Point{ 5.0, 0.0 }, 2.0, 0.5));
    shapes.push_back(std::move(composite));

    shapes.push_back(std::make_unique<IsoscelesTrapezoid>(Point{ -5.0, -2.0 }, 5.0, 3.0, 2.0));

    std::cout << "=== Formes abans de fer zoom === " << std::endl;
    for (const auto& shape : shapes) {
        printShapeInfo(*shape);
    }

    std::cout << "\n=== Escalat per 2 vegades ===" << std::endl;
    for (auto& shape : shapes) {
        shape->scale(2.0);
    }

    std::cout << "\n=== Formes després de fer zoom === " << std::endl;
    for (const auto& shape : shapes) {
        printShapeInfo(*shape);
    }

    return 0;
}

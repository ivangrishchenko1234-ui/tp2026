#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "rectangle.h"
#include "ring.h"
#include "rhombus.h"
#include "compositeshape.h"

void printShapeInfo(const Shape& shape) {
    Point center = shape.getCenter();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[" << shape.getName() << ", (" << center.x << ", " << center.y << "), " << shape.getArea() << "]";
}

void printCompositeInfo(const CompositeShape& composite) {
    Point center = composite.getCenter();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[COMPOSITE, (" << center.x << ", " << center.y << "), " << composite.getArea() << ":\n";

    for (const auto& shape : composite.getShapes()) {
        std::cout << "  ";
        printShapeInfo(*shape);
        std::cout << "\n";
    }
    std::cout << "]";
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(
        Point(0, 0), Point(6, 4)));

    shapes.push_back(std::make_unique<Ring>(
        Point(10, 5), 5.0, 2.0));

    shapes.push_back(std::make_unique<Rhombus>(
        Point(-5, -2), 8.0, 6.0));

    shapes.push_back(std::make_unique<Rectangle>(
        Point(-10, 2), Point(-6, 5)));

    shapes.push_back(std::make_unique<Ring>(
        Point(0, 10), 3.0, 1.0));

    auto composite = std::make_unique<CompositeShape>();

    composite->addShape(std::make_unique<Rectangle>(
        Point(15, 15), Point(20, 18)));

    composite->addShape(std::make_unique<Ring>(
        Point(18, 20), 2.5, 1.0));

    composite->addShape(std::make_unique<Rhombus>(
        Point(22, 17), 5.0, 4.0));

    shapes.push_back(std::move(composite));

    std::cout << "=== Фигуры до масштабирования ===\n";
    std::cout << "Варианты: 0 - Прямоугольник, 2 - Кольцо, 5 - Ромб\n\n";

    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << "Фигура " << i + 1 << ": ";
        if (shapes[i]->getName() == "COMPOSITE") {
            printCompositeInfo(dynamic_cast<const CompositeShape&>(*shapes[i]));
        } else {
            printShapeInfo(*shapes[i]);
        }
        std::cout << "\n\n";
    }

    std::cout << "\n=== Масштабирование всех фигур в 2 раза ===\n\n";
    for (auto& shape : shapes) {
        shape->scale(2.0);
    }

    std::cout << "=== Фигуры после масштабирования (x2) ===\n\n";
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << "Фигура " << i + 1 << ": ";
        if (shapes[i]->getName() == "COMPOSITE") {
            printCompositeInfo(dynamic_cast<const CompositeShape&>(*shapes[i]));
        } else {
            printShapeInfo(*shapes[i]);
        }
        std::cout << "\n\n";
    }

    return 0;
}


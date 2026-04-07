#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include "rectangle.h"
#include "circle.h"
#include "rombus.h"
#include "composite_shape.h"

void printShape(const Shape& shape) {
    Point c = shape.getCenter();
    const CompositeShape* comp = dynamic_cast<const CompositeShape*>(&shape);
    if (comp) {
        std::cout << "[COMPOSITE, (" << std::fixed << std::setprecision(2)
                  << c.x << ", " << c.y << "), " << shape.getArea() << ":\n";
        for (size_t i = 0; i < comp->getSize(); ++i) {
            const Shape* inner = comp->getShape(i);
            Point ic = inner->getCenter();
            std::cout << " " << inner->getName() << ", (" << std::fixed << std::setprecision(2)
                      << ic.x << ", " << ic.y << "), " << inner->getArea() << ",\n";
        }
        std::cout << "]\n";
    } else {
        std::cout << "[" << shape.getName() << ", (" << std::fixed << std::setprecision(2)
                  << c.x << ", " << c.y << "), " << shape.getArea() << "]\n";
    }
}

int main() {
    try {
        auto comp = std::make_unique<CompositeShape>();
        comp->addShape(std::make_unique<Rectangle>(Point{0.0, 0.0}, Point{4.0, 2.0}));
        comp->addShape(std::make_unique<Circle>(Point{10.0, 10.0}, 5.0));

        std::vector<std::unique_ptr<Shape>> shapes;
        shapes.push_back(std::move(comp));
        shapes.push_back(std::make_unique<Rectangle>(Point{1.0, 1.0}, Point{3.0, 3.0}));
        shapes.push_back(std::make_unique<Circle>(Point{-10.0, -10.0}, 2.0));
        shapes.push_back(std::make_unique<Rombus>(Point{-5.0, -5.0}, 4.0, 6.0));
        shapes.push_back(std::make_unique<Rombus>(Point{5.0, 5.0}, 2.0, 2.0));

        for (const auto& s : shapes) {
            printShape(*s);
        }

        std::cout << "\n";

        const double scaleFactor = 2.0;
        for (const auto& s : shapes) {
            s->scale(scaleFactor);
        }

        for (const auto& s : shapes) {
            printShape(*s);
        }

        std::cout << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

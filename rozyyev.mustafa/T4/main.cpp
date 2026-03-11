#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <cstdlib>
#include "rectangle.h"
#include "ring.h"
#include "trapezoid.h"
#include "composite-shape.h"

void printShape(const Shape& s) {
    Point c = s.getCenter();
    std::cout << "[" << s.getName() << ", ("
        << std::fixed << std::setprecision(2) << c.x << ", " << c.y
        << "), " << s.getArea() << "]";

    const CompositeShape* comp = dynamic_cast<const CompositeShape*>(&s);
    if (comp) {
        std::cout << ":";
        const auto& children = comp->getShapes();
        for (size_t i = 0; i < children.size(); ++i) {
            std::cout << "\n";
            Point cc = children[i]->getCenter();
            std::cout << children[i]->getName() << ", ("
                << std::fixed << std::setprecision(2) << cc.x << ", " << cc.y
                << "), " << children[i]->getArea();
            if (i != children.size() - 1) std::cout << ",";
        }
    }
    std::cout << "\n";
}

int main() {
    try {
        std::vector<std::unique_ptr<Shape>> shapes;

        shapes.push_back(std::make_unique<Rectangle>(Point{ 0,0 }, Point{ 2,2 }));
        shapes.push_back(std::make_unique<Ring>(Point{ 10,10 }, 2, 5));
        shapes.push_back(std::make_unique<Trapezoid>(Point{ 0,0 }, 4, 2, 3));
        shapes.push_back(std::make_unique<Rectangle>(Point{ 5,5 }, Point{ 7,7 }));

        auto comp = std::make_unique<CompositeShape>();
        comp->add(std::make_unique<Rectangle>(Point{ 1,1 }, Point{ 3,3 }));
        comp->add(std::make_unique<Ring>(Point{ 2,2 }, 1, 2));
        shapes.push_back(std::move(comp));

        std::cout << "Before scale:\n";
        for (const auto& s : shapes) {
            printShape(*s);
        }

        std::cout << "\nAfter scale (x2):\n";
        for (auto& s : shapes) {
            s->scale(2.0);
            printShape(*s);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

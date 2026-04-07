#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "rectangle.h"
#include "circle.h"
#include "rhombus.h"
#include "compositeshape.h"

static void printShape(const Shape& shape) {
    std::cout << std::fixed << std::setprecision(2);
    Point c = shape.getCenter();

    const CompositeShape* comp = dynamic_cast<const CompositeShape*>(&shape);
    if (comp) {
        std::cout << "[" << shape.getName() << ", (" << c.x << ", " << c.y
                  << "), " << shape.getArea() << ":" << std::endl;

        const auto& subs = comp->getShapes();
        for (size_t i = 0; i < subs.size(); ++i) {
            Point sc = subs[i]->getCenter();
            std::cout << "  " << subs[i]->getName() << ", (" << sc.x
                      << ", " << sc.y << "), " << subs[i]->getArea();
            if (i + 1 < subs.size()) {
                std::cout << ",";
            }
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl;
    } else {
        std::cout << "[" << shape.getName() << ", (" << c.x << ", " << c.y
                  << "), " << shape.getArea() << "]" << std::endl;
    }
}

int main() {
    const double SCALE_FACTOR = 2.0;

    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
    shapes.push_back(std::make_unique<Circle>(Point(5, 5), 2.0));
    shapes.push_back(std::make_unique<Rhombus>(Point(10, 10), 6.0, 4.0));
    shapes.push_back(std::make_unique<Rectangle>(Point(2, 2), Point(6, 5)));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Circle>(Point(15, 15), 3.0));
    composite->addShape(std::make_unique<Rhombus>(Point(20, 20), 8.0, 6.0));
    composite->addShape(std::make_unique<Rectangle>(Point(12, 12), Point(18, 18)));
    shapes.push_back(std::move(composite));

    std::cout << "Before scaling:" << std::endl;
    std::cout << "================" << std::endl;
    for (const auto& s : shapes) {
        printShape(*s);
    }

    for (auto& s : shapes) {
        s->scale(SCALE_FACTOR);
    }

    std::cout << std::endl << "After scaling (x2):" << std::endl;
    std::cout << "======================" << std::endl;
    for (const auto& s : shapes) {
        printShape(*s);
    }

    return 0;
}

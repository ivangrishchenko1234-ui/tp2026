#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include "rectangle.h"
#include "ellipse.h"
#include "square.h"
#include "composite_shape.h"

void printShapesInfo(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        Point center = shape->getCenter();
        if (shape->getName() == "COMPOSITE") {
            std::cout << "[" << shape->getName() << ", ("
                      << std::fixed << std::setprecision(2) << center.x << ", "
                      << std::setprecision(2) << center.y << "), "
                      << std::setprecision(2) << shape->getArea() << ":"
                      << std::endl;
            const CompositeShape* composite = dynamic_cast<const CompositeShape*>(shape.get());
            if (composite) {
                const auto& innerShapes = composite->getShapes();
                for (size_t i = 0; i < innerShapes.size(); ++i) {
                    const auto& innerShape = innerShapes[i];
                    Point innerCenter = innerShape->getCenter();
                    std::cout << " " << innerShape->getName() << ", ("
                              << std::fixed << std::setprecision(2) << innerCenter.x << ", "
                              << std::setprecision(2) << innerCenter.y << "), "
                              << std::setprecision(2) << innerShape->getArea();
                    if (i < innerShapes.size() - 1) {
                        std::cout << ",";
                    }
                    std::cout << std::endl;
                }
            }
            std::cout << "]" << std::endl;
        } else {
            std::cout << "[" << shape->getName() << ", ("
                      << std::fixed << std::setprecision(2) << center.x << ", "
                      << std::setprecision(2) << center.y << "), "
                      << std::setprecision(2) << shape->getArea() << "]"
                      << std::endl;
        }
    }
}
int main() {
    double factor;
    if (!(std::cin >> factor)) {
        std::cerr << "Shapes description without scaling, non-zero exit code and error message in standard error." << std::endl;
        return 2;
    }
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
    shapes.push_back(std::make_unique<Ellipse>(Point(5, 5), 2.0, 1.5));
    shapes.push_back(std::make_unique<Square>(Point(10, 0), 2.5));
    shapes.push_back(std::make_unique<Rectangle>(Point(-2, -1), Point(1, 2)));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point(2, 2), Point(5, 4)));
    composite->addShape(std::make_unique<Ellipse>(Point(3, 6), 1.0, 1.0));
    composite->addShape(std::make_unique<Square>(Point(7, 3), 1.8));

    shapes.push_back(std::move(composite));

    std::cout << "=== BEFORE SCALING ===" << std::endl;
    printShapesInfo(shapes);

    std::cout << "\n=== BONUS 1: POINT CONTAINS TEST ===" << std::endl;
    Point testPoint(2.5, 1.8);
    std::cout << "Testing point (2.50, 1.80):" << std::endl;
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << " Shape " << i << " (" << shapes[i]->getName() << "): ";
        if (shapes[i]->containsPoint(testPoint)) {
            std::cout << "INSIDE" << std::endl;
        } else {
            std::cout << "OUTSIDE" << std::endl;
        }
    }
    std::cout << "\n=== BONUS 2: PERIMETER TEST ===" << std::endl;
    std::cout << "Perimeter of each shape:" << std::endl;
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << " Shape " << i << " (" << shapes[i]->getName() << "): "
                  << std::fixed << std::setprecision(2) << shapes[i]->getPerimeter()
                  << std::endl;
    }
    std::cout << "\n* For ellipse, Ramanujan's approximation formula is used." << std::endl;
    std::cout << "\n--- SCALING BY FACTOR " << std::fixed << std::setprecision(1) << factor << " ---" << std::endl;
    for (auto& shape : shapes) {
        shape->scale(factor);
    }
    std::cout << "\n=== AFTER SCALING ===" << std::endl;
    printShapesInfo(shapes);

    std::cout << "\n=== BONUS 1: POINT CONTAINS TEST (AFTER SCALING) ===" << std::endl;
    std::cout << "Testing point (2.50, 1.80) after scaling:" << std::endl;
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << " Shape " << i << " (" << shapes[i]->getName() << "): ";
        if (shapes[i]->containsPoint(testPoint)) {
            std::cout << "INSIDE" << std::endl;
        } else {
            std::cout << "OUTSIDE" << std::endl;
        }
    }
    return 0;
}
//

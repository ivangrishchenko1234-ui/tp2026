#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include "Shape.hpp"
#include "Composite_shape.hpp"
#include "Ellipse.hpp"
#include "Rectangle.hpp"
#include "Right_trapezoid.hpp"

void printInfo(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        Point center = shape->getCenter();
        std::cout << "[" << shape->getName() << ",("
            << std::fixed << std::setprecision(2) << center.x << ", "
            << center.y << "), "
            << shape->getArea() << "]";

        if (shape->getName() == "COMPOSITE") {
            const CompositeShape* composite = dynamic_cast<const CompositeShape*>(shape.get());
            if (composite) {
                std::cout << ":";
                for (const auto& subShape : composite->getShapes()) {
                    Point subCenter = subShape->getCenter();
                    std::cout << "\n  [" << subShape->getName() << ",("
                        << std::fixed << std::setprecision(2) << subCenter.x << ", "
                        << subCenter.y << "), "
                        << subShape->getArea() << "]";
                }
            }
        }
        std::cout << '\n';
    }
}

int main(int /* argc */, char* /* argv */[]) {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point{ 0, 0 }, Point{ 2, 3 }));
    shapes.push_back(std::make_unique<Ellipse>(Point{ 5, 5 }, 2.0, 1.5));
    shapes.push_back(std::make_unique<RightTrapezoid>(Point{ 1, 1 }, 4.0, 2.0, 2.0));
    shapes.push_back(std::make_unique<Rectangle>(Point{ 3, 2 }, Point{ 5, 4 }));
    shapes.push_back(std::make_unique<Ellipse>(Point{ -2, -1 }, 1.0, 0.5));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point{ 1, 2 }, Point{ 3, 5 }));
    composite->addShape(std::make_unique<Ellipse>(Point{ 4, 3 }, 1.0, 2.0));
    shapes.push_back(std::move(composite));

    std::cout << "BEFORE SCALING:\n";
    printInfo(shapes);

    for (auto& shape : shapes) {
        shape->scale(2.0);
    }

    std::cout << "\nAFTER SCALING:\n";
    printInfo(shapes);

    return 0;
}

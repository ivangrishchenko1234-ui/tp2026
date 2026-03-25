#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include "rectangle.h"
#include "circle.h"
#include "rhombus.h"
#include "compositeShape.h"

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(Point(1, 1), Point(4, 3)));
    shapes.push_back(std::make_unique<Circle>(Point(0, 0), 2));
    shapes.push_back(std::make_unique<Rhombus>(Point(3, 2), 4, 6));
    shapes.push_back(std::make_unique<Circle>(Point(-2, 3), 1.5));
    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point(2, 2), Point(5, 4)));
    composite->addShape(std::make_unique<Circle>(Point(4, 3), 1));
    composite->addShape(std::make_unique<Rhombus>(Point(3, 5), 3, 4));
    shapes.push_back(std::move(composite));
    double factorInput;
    std::cin >> factorInput;
    if (std::cin.fail()) {
        if (std::cin.eof()) {
            factorInput = 1.0;
        } else {
            std::cerr << "ERROR. Wrong data format\n";
            return 1;
        }
    }
    std::cout << "before:" << std::endl;
    for (const auto& s : shapes) {
        Point c = s->getCenter();
        std::cout << "[" << s->getName() << ", (" << c.x << ", " << c.y << "), "
            << s->getArea() << "]" << std::endl;
    }
    for (auto& s : shapes)
        s->scale(factorInput);
    std::cout << "after:" << std::endl;
    for (const auto& s : shapes) {
        Point c = s->getCenter();
        std::cout << "[" << s->getName() << ", (" << c.x << ", " << c.y << "), "
            << s->getArea() << "]" << std::endl;
    }
    return 0;
}

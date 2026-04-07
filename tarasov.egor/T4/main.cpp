#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <stdexcept>
#include "rectangle.h"
#include "circle.h"
#include "rhomb.h"
#include "compositeShape.h"

void printShapes(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (size_t i = 0; i < shapes.size(); ++i) {
        CompositeShape* comp = dynamic_cast<CompositeShape*>(shapes[i].get());
        if (comp) {
            std::cout << *comp << "\n";
        } else {
            std::cout << *shapes[i] << "\n";
        }
    }
}
int main() {
    try {
        std::cout << std::fixed << std::setprecision(2);
        std::vector<std::unique_ptr<Shape>> shapes;
        shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(3, 4)));
        shapes.push_back(std::make_unique<Circle>(Point(2, 2), 3));
        shapes.push_back(std::make_unique<Rhomb>(Point(5, 5), 4, 6));
        shapes.push_back(std::make_unique<Rectangle>(Point(-3, -2), Point(1, 2)));
        shapes.push_back(std::make_unique<Circle>(Point(-2, 3), 2.5));
        auto composite = std::make_unique<CompositeShape>();
        composite->addShape(std::make_unique<Rectangle>(Point(0, 0), Point(2, 2)));
        composite->addShape(std::make_unique<Circle>(Point(3, 3), 1.5));
        composite->addShape(std::make_unique<Rhomb>(Point(1, 5), 3, 4));
        shapes.push_back(std::move(composite));
        printShapes(shapes);
        for (size_t i = 0; i < shapes.size(); ++i) {
            shapes[i]->scale(2);
        }
        std::cout << '\n';
        printShapes(shapes);
        return 0;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

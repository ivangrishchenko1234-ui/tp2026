#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include "Rectangle.h"
#include "Ellipse.h"
#include "Square.h"
#include "CompositShape.h"
#include "Point.h"

void printShapes(const std::vector<std::unique_ptr<Shape>>& container) {
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& s : container) {
        s->print(std::cout);
    }
}

int main() {
    try {
        std::vector<std::unique_ptr<Shape>> myShapes;

        myShapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(2, 4)));
        myShapes.push_back(std::make_unique<Square>(Point(5, 5), 2.0));
        myShapes.push_back(std::make_unique<Ellipse>(1.0, 2.0, Point(10, 10)));

        auto composite = std::make_unique<CompositeShape>();
        composite->addShape(std::make_unique<Rectangle>(Point(0, 0), Point(1, 1)));
        composite->addShape(std::make_unique<Square>(Point(2, 2), 1.0));
        composite->addShape(std::make_unique<Ellipse>(1.0, 2.0, Point(10, 10)));
        composite->addShape(std::make_unique<Square>(Point(8, 8), 1.5));
        composite->addShape(std::make_unique<Ellipse>(2.0, 3.0, Point(12, 12)));

        myShapes.push_back(std::move(composite));

        std::cout << "--- BEFORE SCALE ---\n";
        printShapes(myShapes);

        const double factor = 2.0;
        for (auto& s : myShapes) {
            s->scale(factor);
        }

        std::cout << "\n--- AFTER SCALE (x" << factor << ") --- \n";
        printShapes(myShapes);
    }
    catch (...) {
        std::cerr << "UNKNOWN ERROR\n";
    }
    return 0;
}

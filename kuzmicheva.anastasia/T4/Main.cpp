#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "CompositeShape.h"
#include "Rhomb.h"
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"

void printinfo(const std::vector<std::unique_ptr<Shape>>& figures) {
    if (figures.empty()) {
        throw std::runtime_error("ERROR: the shapes container is empty!\n");
    }
    else {
        for (size_t i = 0; i < figures.size(); i++) {
            figures[i]->info();
        }
    }
}

int main() {
    try {

        std::cout << std::fixed << std::setprecision(2);

        std::vector<std::unique_ptr<Shape>> shapes;

        shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(2.7, 4.4)));
        shapes.push_back(std::make_unique<Circle>(Point(3.3, 5.7), 6.8));
        shapes.push_back(std::make_unique<Rhomb>(Point(7.7, 9), 4, 6.8));

        auto rect = std::make_unique<Rectangle>(Point(0, 0), Point(2, 2));
        auto circ = std::make_unique<Circle>(Point(5, 5), 3.0);
        auto rhom = std::make_unique<Rhomb>(Point(10, 10), 4.0, 6.0);

        auto group = std::make_unique<CompositeShape>();
        group->add(std::move(rect));
        group->add(std::move(circ));
        group->add(std::move(rhom));

        shapes.push_back(std::move(group));

        printinfo(shapes);

        for (size_t i = 0; i < shapes.size(); i++) {
            shapes[i]->scale(2.0);
        }

        printinfo(shapes);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

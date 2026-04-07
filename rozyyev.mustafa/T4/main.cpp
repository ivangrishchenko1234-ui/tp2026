#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <stdexcept>
#include <cstdlib>

#include "rectangle.h"
#include "ring.h"
#include "trapezoid.h"
#include "composite-shape.h"

int main() {
    try {
        std::vector<std::unique_ptr<Shape>> shapes;

        shapes.push_back(std::make_unique<Rectangle>(Point{ 0,0 }, Point{ 2,2 }));
        shapes.push_back(std::make_unique<Ring>(Point{ 10,10 }, 2, 5));
        shapes.push_back(std::make_unique<Trapezoid>(Point{ 0,0 }, 4, 2, 3));
        shapes.push_back(std::make_unique<Rectangle>(Point{ 5,5 }, Point{ 7,7 }));

        auto composite = std::make_unique<CompositeShape>();
        composite->add(std::make_unique<Rectangle>(Point{ 1,1 }, Point{ 3,3 }));
        composite->add(std::make_unique<Ring>(Point{ 2,2 }, 1, 2));
        shapes.push_back(std::move(composite));

        std::cout << std::fixed << std::setprecision(2);

        std::cout << "Before scale:\n";
        for (size_t i = 0; i < shapes.size(); i++) {
            std::cout << shapes[i]->getName() << ", ("
                << shapes[i]->getCenter().x << ", "
                << shapes[i]->getCenter().y << "), "
                << shapes[i]->getArea() << "\n";
        }

        double factor;
        std::cout << "Enter scale factor: ";
        std::cin >> factor;

        if (std::cin.fail()) {
            std::cerr << "Error: Invalid scale factor input" << std::endl;
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < shapes.size(); i++) {
            shapes[i]->scale(factor);
        }

        std::cout << "\nAfter scale:\n";
        for (size_t i = 0; i < shapes.size(); i++) {
            std::cout << shapes[i]->getName() << ", ("
                << shapes[i]->getCenter().x << ", "
                << shapes[i]->getCenter().y << "), "
                << shapes[i]->getArea() << "\n";
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

#include "rectangle.h"
#include "ring.h"
#include "trap.h"
#include "complex.h"

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point(0,0), Point(4,2)));
    shapes.push_back(std::make_unique<Ring>(Point(5,5), 3, 1));
    shapes.push_back(std::make_unique<Trap>(Point(1,1), 4, 2, 3));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point(2,2), Point(5,4)));
    composite->addShape(std::make_unique<Ring>(Point(6,6), 2, 1));
    shapes.push_back(std::move(composite));

    std::cout << std::fixed << std::setprecision(2);
    size_t size= shapes.size();

    for (size_t i = 0;i<size;i++) {
        std::cout << shapes[i]->getName() << ", ("<< shapes[i]->getCenter().x_ <<\
         "," << shapes[i]->getCenter().y_<< "), " << shapes[i]->getArea() << "\n";
    }
    for (size_t i = 0;i<size;i++) {
        shapes[i]->scale(2.0);
    }

    for (size_t i = 0;i<size;i++) {
        std::cout << shapes[i]->getName() << ", ("<< shapes[i]->getCenter().x_ <<\
         "," << shapes[i]->getCenter().y_<< "), " << shapes[i]->getArea() << "\n";
    }

    return 0;
}
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <stdexcept>

#include "rectangle.h"
#include "ring.h"
#include "trap.h"
#include "complex.h"

int main() {
    try{

        std::vector<std::unique_ptr<Shape>> shapes;

        shapes.push_back(std::make_unique<Rectangle>(Point(0,0), Point(4,2)));
        shapes.push_back(std::make_unique<Ring>(Point(5,5), 3, 1));
        shapes.push_back(std::make_unique<Trap>(Point(1,1), 4, 2, 3));
        shapes.push_back(std::make_unique<Rectangle>(Point(5,6), Point(10,15)));

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
         double factor;
        std::cin>>factor;
        if(std::cin.fail()){
            std::cerr << "Error: Invalid scale factor input" << std::endl;
            return 1;
    }
        for (size_t i = 0;i<size;i++) {
            shapes[i]->scale(factor);
        }

        for (size_t i = 0;i<size;i++) {
            std::cout << shapes[i]->getName() << ", ("<< shapes[i]->getCenter().x_ <<\
            "," << shapes[i]->getCenter().y_<< "), " << shapes[i]->getArea() << "\n";
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

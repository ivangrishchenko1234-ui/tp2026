#include "Rectangle.h"
#include "CompositeShape.h"
#include "Ring.h"
#include "Square.h"

#include <iostream>
#include <type_traits>
#include <iomanip>

template<class T>
typename std::enable_if_t<std::is_base_of<Shape, T>::value, void>
print(const std::unique_ptr<T>& shp) {
    if (auto comp = dynamic_cast<CompositeShape*>(shp.get())) {
        std::cout   << "["
                    << comp->getName()
                    << ", (" << comp->getCenter().x_
                    << ", "
                    << comp->getCenter().y_ << ")"
                    << ", " << comp->getArea() << " :" << std::endl;

        for (const auto& shape : comp->getVec()) {
            std::cout << "    ";
            print(shape);
        }
        return;
    }

    std::cout   << "[" << shp->getName()
                << ", (" << shp->getCenter().x_
                << ", "
                << shp->getCenter().y_ << ")"
                << ", " << shp->getArea();

    std::cout << "]" << std::endl;
}

int main() {
    try {
        std::cout << std::fixed << std::setprecision(2);
        //preparing & testing
        Point p1(1.0, 1.5);
        Point p2(2.0, 8.3);
        Point p3(3.0, 12.5);
        Point p4(6.0, 1.7);
        Point p5(1.4, 6.5);
        Point p6(-9.0, -0.5);

        std::vector<std::unique_ptr<Shape>> shapes;
        auto compShape = std::make_unique<CompositeShape>();
        auto sqr = std::make_unique<Square>(p1, 2.0);
        auto sqr2 = std::make_unique<Square>(p5, 3.0);
        auto ring = std::make_unique<Ring>(p2, 5.0, 2.0);
        auto rec = std::make_unique<Rectangle>(p6, p3);
        compShape->push_back(std::move(sqr2));
        compShape->push_back(std::move(ring));
        compShape->push_back(std::move(rec));

        //filling shapes
        shapes.push_back(std::move(sqr));
        shapes.push_back(std::move(compShape));
        shapes.push_back(std::make_unique<Square>(p5, 9.0));
        shapes.push_back(std::make_unique<Ring>(Point(0.0, 5.0), 10.0, 5.0));
        shapes.push_back(std::make_unique<Rectangle>(p5, p3));
        shapes.push_back(std::make_unique<Square>(p4, 3.5));

        std::cout << "\n------BEFORE SCALE------" << std::endl;
        //printing
        for (const auto& i : shapes) {
            print(i);
        }

        double factor;
        if (!(std::cin >> factor)) {
            std::cerr << "ERROR: Factor cin failed" << std::endl;
            return 1;
        }

        if (factor <= 0.0) {
            std::cerr << "ERROR: Factor must be positive" << std::endl;
            return 1;
        }

        std::cout << "\n------AFTER SCALE------" << std::endl;

        for (const auto& i : shapes) {
            i->scale(factor);
        }

        for (const auto& i : shapes) {
            print(i);
        }

        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "ERROR:" << e.what() << std::endl;
        return 1;
    }

    return 0;
}

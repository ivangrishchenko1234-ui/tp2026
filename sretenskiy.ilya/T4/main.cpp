#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include "rectangle.h"
#include "square.h"
#include "ring.h"
#include "composite_shape.h"

void printShapeInfo(const Shape& shape, int indent = 0) {
    if (shape.getName() == "COMPOSITE") {
        const CompositeShape& comp = dynamic_cast<const CompositeShape&>(shape);
        std::cout << std::string(indent, ' ') << "[COMPOSITE, ("
            << std::fixed << std::setprecision(2) << comp.getCenter().x << ", "
            << std::setprecision(2) << comp.getCenter().y << "), "
            << std::setprecision(2) << comp.getArea() << ":";
        const auto& children = comp.getShapes();
        for (size_t i = 0; i < children.size(); ++i) {
            std::cout << std::endl;
            std::cout << std::string(indent + 2, ' ') << children[i]->getName() << ", ("
                << std::fixed << std::setprecision(2) << children[i]->getCenter().x << ", "
                << std::setprecision(2) << children[i]->getCenter().y << "), "
                << std::setprecision(2) << children[i]->getArea();
            if (i != children.size() - 1) std::cout << ",";
        }
        std::cout << "]";
    }
    else {
        std::cout << std::string(indent, ' ') << "[" << shape.getName() << ", ("
            << std::fixed << std::setprecision(2) << shape.getCenter().x << ", "
            << std::setprecision(2) << shape.getCenter().y << "), "
            << std::setprecision(2) << shape.getArea() << "]";
    }
}

void printAllShapes(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        printShapeInfo(*shape);
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    // Прямоугольник
    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(2, 3)));   
    shapes.push_back(std::make_unique<Rectangle>(Point(1, 1), Point(4, 4)));  

    // Квадрат
    shapes.push_back(std::make_unique<Square>(Point(5, 5), 2.0));              

    // Кольцо
    shapes.push_back(std::make_unique<Ring>(Point(10, 10), 3.0, 1.0));         

    // Сосатвная (квадрат + кольцо)
    auto comp = std::make_unique<CompositeShape>();
    comp->addShape(std::make_unique<Square>(Point(15, 15), 2.0));              
    comp->addShape(std::make_unique<Ring>(Point(20, 15), 2.0, 0.5));           
    shapes.push_back(std::move(comp));

   
    shapes.push_back(std::make_unique<Rectangle>(Point(-2, -2), Point(0, 0))); 

    std::cout << "Before scaling:" << std::endl;
    printAllShapes(shapes);

    
    for (auto& shape : shapes) shape->scale(2.0);

    std::cout << "\nAfter scaling by 2:" << std::endl;
    printAllShapes(shapes);

    return 0;
}
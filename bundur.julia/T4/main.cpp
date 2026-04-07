#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <string>
#include "Point.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Rectangular_trapezoid.h"
#include "Composite_shape.h"
void printShapeInfo(const std::shared_ptr<Shape>& shape) {
    if (!shape) return;
    Point center = shape->getCenter();
    std::cout<<std::fixed<<std::setprecision(2)<<"["<<shape->getName()<<", ("<<center.x<<", "<<center.y<<"), "<<shape->getArea()<<"]";
}
int main() {
    std::vector<std::shared_ptr<Shape>> shapes;
    try {
        shapes.push_back(std::make_shared<Rectangle>(Point{1.0, 1.0}, Point{4.0, 5.0}));
        shapes.push_back(std::make_shared<Ellipse>(Point{10.0, 10.0}, 2.0, 5.0));
        shapes.push_back(std::make_shared<RectangularTrapezoid>(Point{0.0, 0.0}, 6.0, 4.0, 3.0));
        shapes.push_back(std::make_shared<Rectangle>(Point{-5.0, -5.0}, Point{-2.0, -2.0}));
        auto composite = std::make_shared<CompositeShape>();
        composite->addShape(std::make_shared<Rectangle>(Point{0.0, 0.0}, Point{2.0, 2.0}));
        composite->addShape(std::make_shared<Ellipse>(Point{1.0, 1.0}, 0.5, 0.5));
        shapes.push_back(composite);
        for (size_t i = 0; i < shapes.size(); ++i) {
            std::cout<<i + 1<<". ";
            printShapeInfo(shapes[i]);
            std::cout<<"\n";
        }
        std::cout<<"\n";
        for (size_t i = 0; i < shapes.size(); ++i) {
            shapes[i]->scale(2.0);
            std::cout << i + 1 << ". ";
            printShapeInfo(shapes[i]);
            std::cout<<"\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr<<"Error: "<<e.what()<<"\n";
        return 1;
    }
    return 0;
}


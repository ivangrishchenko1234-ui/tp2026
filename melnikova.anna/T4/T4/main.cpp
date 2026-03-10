#include <iostream>

#include <vector>
#include <memory>
#include <iomanip>
#include "point.h"
#include "shape.h"
#include "rectangle.h"
#include "circle.h"
#include "isosceles_trapezoid.h"
#include "composite_shape.h"

static void printShape(const Shape& s) {
    Point c = s.getCenter();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[" << s.getName() << ", (" << c.x << ", " << c.y << ")" << ", " << s.getArea() << "]" << std::endl;
}


static void printComposite(const CompositeShape& cs) {
    Point c = cs.getCenter();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[COMPOSITE, (" << c.x << ", " << c.y << "), " << cs.getArea() << ":" << std::endl;
    for (std::size_t i = 0; i < cs.size(); ++i) {
        const Shape& s = cs.getShape(i);
        Point sc = s.getCenter();
        std::cout << "  " << s.getName() << ", (" << sc.x << ", " << sc.y << ")" << ", " << s.getArea();
        if (i + 1 < cs.size()) std::cout << ",";
        std::cout << std::endl;
    }
    std::cout << "]" <<std::endl;
}


int main(){
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<IsoscelesTrapezoid>(Point{ 0.0, 0.0 }, 6.0, 4.0, 2.0));
    shapes.push_back(std::make_unique<IsoscelesTrapezoid>(Point{ 1.0, 2.0 }, 4.0, 2.0, 2.0));
    shapes.push_back(std::make_unique<IsoscelesTrapezoid>(Point{ 2.0, 4.0 }, 2.0, 1.0, 2.0));
    shapes.push_back(std::make_unique<Circle>(Point{ 3.0, 7.0 }, 1.0));

    auto composite = std::make_unique<CompositeShape>(std::move(shapes));

    Rectangle rect1({ 1.0, 1.0 }, { 4.0, 3.0 });
    Rectangle rect2({ 0.0, 0.0 }, { 5.0, 2.0 });
    Circle    circ1({ 2.0, 2.0 }, 3.0);
    IsoscelesTrapezoid trap1({ 0.0, 0.0 }, 8.0, 4.0, 3.0);

    std::cout << "========== before scaling ==========\n";
    printShape(rect1);
    printShape(rect2);
    printShape(circ1);
    printShape(trap1);
    printComposite(*composite);

    rect1.scale(2.0);
    rect2.scale(2.0);
    circ1.scale(2.0);
    trap1.scale(2.0);
    composite->scale(2.0);

    std::cout << "\n========== after 2x scaling ==========\n";
    printShape(rect1);
    printShape(rect2);
    printShape(circ1);
    printShape(trap1);
    printComposite(*composite);

    return 0;
}
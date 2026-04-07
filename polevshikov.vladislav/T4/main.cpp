#include <iostream>
#include <iomanip>
#include "composite-shape.h"
#include "rectangle.h"
#include "circle.h"
#include "square.h"

void printInfo(const Shape &shape) {
    Point center = shape.getCenter();
    std::cout << shape.getName() << ":\n";
    std::cout << "  Area: " << shape.getArea() << '\n';
    std::cout << "  Center: (" << center.x << ", " << center.y << ")\n";
}

int main() {
    try {
        auto rect1 = std::make_shared<Rectangle>(Point{0.0, 0.0}, 10.0, 5.0);
        auto circ1 = std::make_shared<Circle>(Point{10.0, 10.0}, 5.0);
        auto rect2 = std::make_shared<Rectangle>(Point{-5.0, -5.0}, 2.0, 2.0);
        auto circ2 = std::make_shared<Circle>(Point{15.0, 0.0}, 3.0);
        auto sqr = std::make_shared<Square>(Point{20.0, 20.0}, 4.0);

        CompositeShape composite;
        composite.add(rect1);
        composite.add(circ1);
        composite.add(rect2);
        composite.add(circ2);
        composite.add(sqr);

        std::cout << "--- BEFORE SCALE ---\n";
        printInfo(composite);

        composite.scale(2.0);

        std::cout << "\n--- AFTER SCALE (x2) ---\n";
        printInfo(composite);

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}

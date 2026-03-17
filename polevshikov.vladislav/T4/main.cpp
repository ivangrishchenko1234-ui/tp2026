#include <iostream>
#include <iomanip>
#include "composite-shape.h"
#include "rectangle.h"
#include "circle.h"

void printInfo(const Shape &shape) {
    Point center = shape.getCenter();
    std::cout << shape.getName() << ":\n";
    std::cout << "  Area: " << shape.getArea() << '\n';
    std::cout << "  Center: (" << center.x << ", " << center.y << ")\n";
}

int main() {
    try {
        auto rect = std::make_shared<Rectangle>(Point{0.0, 0.0}, 10.0, 5.0);
        auto circ = std::make_shared<Circle>(Point{10.0, 10.0}, 5.0);

        CompositeShape composite;
        composite.add(rect);
        composite.add(circ);

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
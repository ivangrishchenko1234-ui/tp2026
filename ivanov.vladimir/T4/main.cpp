#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include "rectangle.h"
#include "circle.h"
#include "rectangle-trapezoid.h"
#include "composite-shape.h"

void printShape(const Shape& shape) {
    Point c = shape.getCenter();
    const CompositeShape* comp = dynamic_cast<const CompositeShape*>(&shape);
    if (comp) {
        std::cout << "[COMPOSITE, (" << std::fixed << std::setprecision(2)
                  << c.x << ", " << c.y << "), " << shape.getArea() << ":\n";
        for (size_t i = 0; i < comp->getSize(); ++i) {
            std::shared_ptr<Shape> inner = comp->getShape(i);
            Point ic = inner->getCenter();
            std::cout << inner->getName() << ", (" << std::fixed << std::setprecision(2)
                      << ic.x << ", " << ic.y << "), " << inner->getArea() << ",\n";
        }
        std::cout << "]\n";
    } else {
        std::cout << "[" << shape.getName() << ", (" << std::fixed << std::setprecision(2)
                  << c.x << ", " << c.y << "), " << shape.getArea() << "]\n";
    }
}

int main() {
    std::vector<std::shared_ptr<Shape>> shapes;
    std::string cmd;
    bool scaled = false;

    while (std::cin >> cmd) {
        if (cmd == "RECTANGLE") {
            double x1, y1, x2, y2;
            if (std::cin >> x1 >> y1 >> x2 >> y2) {
                try { shapes.push_back(std::make_shared<Rectangle>(Point{x1, y1}, Point{x2, y2})); } catch (...) {}
            }
        } else if (cmd == "CIRCLE") {
            double x, y, r;
            if (std::cin >> x >> y >> r) {
                try { shapes.push_back(std::make_shared<Circle>(Point{x, y}, r)); } catch (...) {}
            }
        } else if (cmd == "RECTANGLE_TRAPEZOID") {
            double x, y, bw, tw, h;
            if (std::cin >> x >> y >> bw >> tw >> h) {
                try { shapes.push_back(std::make_shared<RectangleTrapezoid>(Point{x, y}, bw, tw, h)); } catch (...) {}
            }
        } else if (cmd == "SCALE") {
            double cx, cy, f;
            if (std::cin >> cx >> cy >> f) {
                if (f <= 0.0) {
                    std::cerr << "Error: Scale factor must be positive\n";
                    return 1;
                }
                bool hasComp = false;
                for (const auto& s : shapes) {
                    if (dynamic_cast<CompositeShape*>(s.get())) {
                        hasComp = true;
                        break;
                    }
                }
                if (!hasComp && shapes.size() >= 2) {
                    auto comp = std::make_shared<CompositeShape>();
                    comp->addShape(shapes.back());
                    shapes.pop_back();
                    comp->addShape(shapes.back());
                    shapes.pop_back();
                    shapes.push_back(comp);
                }

                for (const auto& s : shapes) {
                    printShape(*s);
                }
                std::cout << "\n";
                for (auto& s : shapes) {
                    try { s->scale(f); } catch (...) {}
                    printShape(*s);
                }
                scaled = true;
                break;
            }
        }
    }

    if (!scaled) {
        for (const auto& s : shapes) {
            printShape(*s);
        }
        std::cerr << "Error: No scaling performed\n";
        return 1;
    }

    return 0;
}

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "Shape.h"
#include "Rectangle.h"
#include "Ring.h"
#include "IsoscelesTrapezoid.h"
#include "CompositeShape.h"

void testResult(bool res, const std::string& testName) {
    std::cout << (res ? "[PASSED]\t" : "[FAILED]\t");
    std::cout << testName << '\n';
}

void testRectangle() {
    std::cout << "\n=== TESTING RECTANGLE ===\n";

    Rectangle rect(Point(1.0, 1.0), Point(5.0, 4.0));

    std::cout << "getCenter(): (" << rect.getCenter().x_ << ", " << rect.getCenter().y_ << ")\n";
    testResult(rect.getCenter().x_ == 3.0 && rect.getCenter().y_ == 2.5, "Rectangle initial center");

    std::cout << "getArea(): " << rect.getArea() << "\n";
    testResult(rect.getArea() == 12.0, "Rectangle initial area");

    std::cout << "getName(): " << rect.getName() << "\n";
    testResult(rect.getName() == "Rectangle", "Rectangle name");

    rect.move(2.0, 3.0);
    std::cout << "After move(2,3): (" << rect.getCenter().x_ << ", " << rect.getCenter().y_ << ")\n";
    testResult(rect.getCenter().x_ == 5.0 && rect.getCenter().y_ == 5.5, "Rectangle move");

    double oldArea = rect.getArea();
    rect.scale(2.0);
    std::cout << "After scale(2): area = " << rect.getArea() << "\n";
    testResult(rect.getArea() == oldArea * 4.0, "Rectangle scale");
}

void testRing() {
    std::cout << "\n=== TESTING RING ===\n";

    Ring ring(2.0, 5.0, Point(0.0, 0.0));

    std::cout << "getCenter(): (" << ring.getCenter().x_ << ", " << ring.getCenter().y_ << ")\n";
    testResult(ring.getCenter().x_ == 0.0 && ring.getCenter().y_ == 0.0, "Ring initial center");

    std::cout << "getArea(): " << ring.getArea() << "\n";
    double expectedArea = 3.1415 * (25.0 - 4.0);
    testResult(std::abs(ring.getArea() - expectedArea) < 0.001, "Ring initial area");

    std::cout << "getName(): " << ring.getName() << "\n";
    testResult(ring.getName() == "Ring", "Ring name");

    ring.move(-1.0, 2.0);
    std::cout << "After move(-1,2): (" << ring.getCenter().x_ << ", " << ring.getCenter().y_ << ")\n";
    testResult(ring.getCenter().x_ == -1.0 && ring.getCenter().y_ == 2.0, "Ring move");

    double oldArea = ring.getArea();
    ring.scale(0.5);
    std::cout << "After scale(0.5): area = " << ring.getArea() << "\n";
    testResult(std::abs(ring.getArea() - oldArea * 0.25) < 0.001, "Ring scale");
}

void testIsoscelesTrapezoid() {
    std::cout << "\n=== TESTING ISOSCELES TRAPEZOID ===\n";

    IsoscelesTrapezoid trap(Point(2.0, 1.0), 6.0, 4.0, 3.0);

    std::cout << "getCenter(): (" << trap.getCenter().x_ << ", " << trap.getCenter().y_ << ")\n";
    testResult(trap.getCenter().x_ == 4.5 && trap.getCenter().y_ == 2.5, "Trapezoid initial center");

    std::cout << "getArea(): " << trap.getArea() << "\n";
    testResult(trap.getArea() == 15.0, "Trapezoid initial area");

    std::cout << "getName(): " << trap.getName() << "\n";
    testResult(trap.getName() == "Isosceles trapezoid", "Trapezoid name");

    trap.move(1.5, 2.5);
    std::cout << "After move(1.5,2.5): (" << trap.getCenter().x_ << ", " << trap.getCenter().y_ << ")\n";
    testResult(trap.getCenter().x_ == 6.0 && trap.getCenter().y_ == 5.0, "Trapezoid move");

    double oldArea = trap.getArea();
    trap.scale(2.0);
    std::cout << "After scale(2): area = " << trap.getArea() << "\n";
    testResult(trap.getArea() == oldArea * 4.0, "Trapezoid scale");
}

void testComposite() {
    std::cout << "\n=== TESTING COMPOSITE SHAPE ===\n";

    auto composite = std::make_unique<CompositeShape>();

    composite->addShape(std::make_unique<Rectangle>(Point(0.0, 0.0), Point(2.0, 2.0)));
    composite->addShape(std::make_unique<Ring>(0.5, 1.0, Point(3.0, 3.0)));
    composite->addShape(std::make_unique<IsoscelesTrapezoid>(Point(4.0, 1.0), 3.0, 2.0, 1.5));

    std::cout << "Initial composite:\n";
    std::cout << "getCenter(): (" << composite->getCenter().x_ << ", " << composite->getCenter().y_ << ")\n";
    Point center = composite->getCenter();
    testResult(center.x_ > 3.4 && center.x_ < 3.6 && center.y_ > 1.9 && center.y_ < 2.1, "Composite initial center");

    double area = composite->getArea();
    std::cout << "getArea(): " << area << "\n";
    double rectArea = 4.0;
    double ringArea = 3.1415 * (1.0 - 0.25);
    double trapArea = 1.5 * (3.0 + 2.0) / 2.0;
    double expectedArea = rectArea + ringArea + trapArea;
    testResult(std::abs(area - expectedArea) < 0.01, "Composite initial area");

    std::cout << "getName(): " << composite->getName();
    testResult(composite->getName() == "Composite Shape\n", "Composite name");

    composite->move(1.0, 1.0);
    std::cout << "After move(1,1): (" << composite->getCenter().x_ << ", " << composite->getCenter().y_ << ")\n";
    Point newCenter = composite->getCenter();
    testResult(newCenter.x_ == center.x_ + 1.0 && newCenter.y_ == center.y_ + 1.0, "Composite move");

    double oldAreaComp = composite->getArea();

    double factor = 1.0;
    std::cout << "Enter scale factor: ";
    if (std::cin >> factor) {
        try {
            composite->scale(factor);
            std::cout << "After scale(" << factor << "): area = " << composite->getArea() << "\n";
            testResult(std::abs(composite->getArea() - oldAreaComp * factor * factor) < 0.01, "Composite scale area");
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Exception: " << e.what() << "\n";
            testResult(false, "Composite scale area (exception)");
        }
    }
    else {
        std::cout << "Invalid input, scale skipped.\n";
        testResult(false, "Composite scale area (no input)");
    }

    const auto& shapes = composite->getShapes();
    bool centersOk = true;
    for (const auto& s : shapes) {
        Point c = s->getCenter();
        if (std::abs(c.x_) > 100 || std::abs(c.y_) > 100) centersOk = false;
    }
    testResult(centersOk, "Composite scale component centers exist");

    std::cout << "Print composite:\n";
    composite->print(std::cout);
    std::cout << "\n";
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::string(40, '=') << "\n";
    std::cout << "\tGEOMETRIC SHAPES TESTING\n";
    std::cout << std::string(40, '=') << "\n";

    testRectangle();
    testRing();
    testIsoscelesTrapezoid();
    testComposite();

    std::cout << "\n" << std::string(40, '=') << "\n";
    std::cout << "\tALL TESTS COMPLETED\n";
    std::cout << std::string(40, '=') << "\n";

    return 0;
}

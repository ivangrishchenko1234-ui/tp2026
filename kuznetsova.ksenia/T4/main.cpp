#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>
#include <clocale>
#include <cmath>

#include "Rectangle.h"
#include "Ring.h"
#include "Square.h"
#include "CompositeShape.h"
#include "Shape.h"
#include "Point.h"

void printShapeInfo(const Shape& shape) {
Point center = shape.getCenter();
std::cout << std::fixed << std::setprecision(2);
std::cout << shape.getName() << ", ("
<< center.x << ", " << center.y << "), "
<< shape.getArea();
}

void printComposite(const CompositeShape& composite) {
std::cout << "[";
printShapeInfo(composite);
std::cout << ";\n";

for (size_t i = 0; i < composite.getSize(); ++i) {
std::cout << " ";
printShapeInfo(*composite.getShape(i));
if (i != composite.getSize() - 1) {
std::cout << ",\n";
}
else {
std::cout << "\n";
}
}
std::cout << "]";
}

void testRectangle() {
std::cout << "\nRECTANGLE TESTING\n";
Rectangle rect(Point(1, 1), Point(5, 4));
std::cout << "Rectangle created with corners (1,1) and (5,4)\n";
std::cout << " ";
printShapeInfo(rect);
std::cout << "\n";

std::cout << "Move by (2, -1):\n";
rect.move(2, -1);
std::cout << " ";
printShapeInfo(rect);
std::cout << "\n";

std::cout << "Scale x2:\n";
rect.scale(2.0);
std::cout << " ";
printShapeInfo(rect);
std::cout << "\n";
}

void testRing() {
std::cout << "\nRING TESTING\n";
Ring ring(Point(3, 3), 5, 2);
std::cout << "Ring created with center (3,3), outer radius=5, inner=2\n";
std::cout << " ";
printShapeInfo(ring);
std::cout << "\n";

std::cout << "Move by (-1, 2):\n";
ring.move(-1, 2);
std::cout << " ";
printShapeInfo(ring);
std::cout << "\n";

std::cout << "Scale x0.5:\n";
ring.scale(0.5);
std::cout << " ";
printShapeInfo(ring);
std::cout << "\n";
}

void testSquare() {
std::cout << "\nSQUARE TESTING\n";
Square square(Point(0, 0), 4);
std::cout << "Square created with bottom-left (0,0) and side=4\n";
std::cout << " ";
printShapeInfo(square);
std::cout << "\n";

std::cout << "Move by (3, 2):\n";
square.move(3, 2);
std::cout << " ";
printShapeInfo(square);
std::cout << "\n";

std::cout << "Scale x1.5:\n";
square.scale(1.5);
std::cout << " ";
printShapeInfo(square);
std::cout << "\n";
}

void testCompositeOperations() {
std::cout << "\nCOMPOSITE OPERATIONS TESTING\n";

CompositeShape composite;
composite.addShape(std::make_unique<Square>(Point(1, 1), 2));
composite.addShape(std::make_unique<Ring>(Point(4, 4), 2, 1));
composite.addShape(std::make_unique<Rectangle>(Point(2, 2), Point(5, 4)));

std::cout << "Composite shape created with 3 elements:\n";
std::cout << " Number of shapes: " << composite.getSize() << "\n";
std::cout << " Total area: " << composite.getArea() << "\n";

Point center = composite.getCenter();
std::cout << " Composite center: (" << center.x << ", " << center.y << ")\n\n";

std::cout << "Component shapes:\n";
for (size_t i = 0; i < composite.getSize(); ++i) {
Shape* shape = composite.getShape(i);
Point c = shape->getCenter();
std::cout << " Shape " << i + 1 << ": " << shape->getName()
<< ", center (" << c.x << ", " << c.y << "), area="
<< shape->getArea() << "\n";
}

std::cout << "\nMove composite by (1, -1):\n";
composite.move(1, -1);
std::cout << "New shape centers:\n";
for (size_t i = 0; i < composite.getSize(); ++i) {
Shape* shape = composite.getShape(i);
Point c = shape->getCenter();
std::cout << " Shape " << i + 1 << ": (" << c.x << ", " << c.y << ")\n";
}

std::cout << "\nScale composite x2:\n";
composite.scale(2.0);
std::cout << "After scaling:\n";
for (size_t i = 0; i < composite.getSize(); ++i) {
Shape* shape = composite.getShape(i);
Point c = shape->getCenter();
std::cout << " Shape " << i + 1 << ": " << shape->getName()
<< ", center (" << c.x << ", " << c.y << "), area="
<< shape->getArea() << "\n";
}
}

void testCompositeScaleExample() {
std::cout << "\nSCALE EXAMPLE TESTING\n";
std::cout << "Example: Circle (2,2) and Rectangle (8,2)\n\n";

CompositeShape composite;

composite.addShape(std::make_unique<Ring>(Point(2, 2), 1, 0));

composite.addShape(std::make_unique<Rectangle>(Point(7, 1), Point(9, 3)));

std::cout << "BEFORE scaling (factor=2):\n";
std::cout << " Composite center: ("
<< composite.getCenter().x << ", "
<< composite.getCenter().y << ")\n";

for (size_t i = 0; i < composite.getSize(); ++i) {
Shape* shape = composite.getShape(i);
Point c = shape->getCenter();
std::cout << " Shape " << i + 1 << ": " << shape->getName()
<< ", center (" << c.x << ", " << c.y << ")\n";
}

std::cout << "\nExecuting scale(2)...\n";
composite.scale(2.0);

std::cout << "\nAFTER scaling:\n";
std::cout << " Composite center: ("
<< composite.getCenter().x << ", "
<< composite.getCenter().y << ")\n";

for (size_t i = 0; i < composite.getSize(); ++i) {
Shape* shape = composite.getShape(i);
Point c = shape->getCenter();
std::cout << " Shape " << i + 1 << ": " << shape->getName()
<< ", center (" << c.x << ", " << c.y << "), area="
<< shape->getArea() << "\n";
}

std::cout << "\nExpected result from example:\n";
std::cout << "Circle should move to (-1,2)\n";
std::cout << "Rectangle should move to (11,2)\n";
}

void testBoundingBox() {
std::cout << "\nBOUNDING BOX TESTING\n";

CompositeShape composite;

composite.addShape(std::make_unique<Square>(Point(0, 0), 1));
composite.addShape(std::make_unique<Square>(Point(8, 0), 1));
composite.addShape(std::make_unique<Square>(Point(0, 6), 1));
composite.addShape(std::make_unique<Square>(Point(8, 6), 1));

std::cout << "Shapes placed at corners:\n";
std::cout << "(0,0), (8,0), (0,6), (8,6)\n";

Point center = composite.getCenter();
std::cout << "Composite center (based on bounding box of centers): ("
<< center.x << ", " << center.y << ")\n";
std::cout << "Expected center: (4, 3)\n";
}

void testEdgeCases() {
std::cout << "\nEDGE CASES TESTING\n";

std::cout << "Empty CompositeShape:\n";
CompositeShape empty;
std::cout << "Size: " << empty.getSize() << "\n";
std::cout << "Is empty? " << (empty.isEmpty() ? "yes" : "no") << "\n";
std::cout << "Area: " << empty.getArea() << "\n";

Point center = empty.getCenter();
std::cout << "Center: (" << center.x << ", " << center.y << ")\n";

std::cout << "\nTrying to get element by index:\n";
try {
empty.getShape(0);
std::cout << "ERROR: should throw exception\n";
}
catch (const std::out_of_range& e) {
std::cout << "Exception: " << e.what() << "\n";
}

std::cout << "\nComposite with single shape:\n";
CompositeShape single;
single.addShape(std::make_unique<Square>(Point(2, 2), 2));

std::cout << "Size: " << single.getSize() << "\n";
std::cout << "Area: " << single.getArea() << "\n";

center = single.getCenter();
std::cout << "Center: (" << center.x << ", " << center.y << ")\n";

Shape* shape = single.getShape(0);
Point c = shape->getCenter();
std::cout << "Shape center: (" << c.x << ", " << c.y << ")\n";

std::cout << "\nScale x3:\n";
single.scale(3.0);

std::cout << "New area: " << single.getArea() << "\n";
center = single.getCenter();
std::cout << "New center: (" << center.x << ", " << center.y << ")\n";

shape = single.getShape(0);
c = shape->getCenter();
std::cout << "New shape center: (" << c.x << ", " << c.y << ")\n";
}

void testMainTask() {
std::cout << "\n";
std::cout << "MAIN TASK (REQUIRED OUTPUT)\n";

std::vector<std::unique_ptr<Shape>> shapes;

shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
shapes.push_back(std::make_unique<Ring>(Point(5, 5), 5, 2));
shapes.push_back(std::make_unique<Square>(Point(2, 2), 3));
shapes.push_back(std::make_unique<Rectangle>(Point(-3, -2), Point(1, 2)));
shapes.push_back(std::make_unique<Ring>(Point(-2, 4), 3, 1));

auto composite = std::make_unique<CompositeShape>();
composite->addShape(std::make_unique<Square>(Point(1, 1), 2));
composite->addShape(std::make_unique<Ring>(Point(3, 3), 2, 1));
composite->addShape(std::make_unique<Rectangle>(Point(2, 0), Point(4, 2)));
shapes.push_back(std::move(composite));

std::cout << "BEFORE scaling (x1):\n";
std::cout << "------------------------\n";

for (const auto& shape : shapes) {
if (shape->getName() == "COMPOSITE") {
printComposite(static_cast<const CompositeShape&>(*shape));
}
else {
std::cout << " ";
printShapeInfo(*shape);
}
std::cout << "\n";
}

std::cout << "\nScaling x2...\n\n";

for (auto& shape : shapes) {
shape->scale(2.0);
}

std::cout << "AFTER scaling (x2):\n";
std::cout << "---------------------------\n";

for (const auto& shape : shapes) {
if (shape->getName() == "COMPOSITE") {
printComposite(static_cast<const CompositeShape&>(*shape));
}
else {
std::cout << " ";
printShapeInfo(*shape);
}
std::cout << "\n";
}
}

int main() {
std::cout << "\n";
std::cout << "SHAPES PROGRAM TESTING\n";

testRectangle();
testRing();
testSquare();

testCompositeOperations();
testCompositeScaleExample();
testBoundingBox();
testEdgeCases();

testMainTask();

if (std::cin.peek() == EOF) {
std::cerr << "Error: No input provided" << std::endl;
return 0;
}

return 0;
}

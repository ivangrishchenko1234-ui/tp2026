#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <stdexcept>

#include "Rectangle.h"
#include "Ring.h"
#include "IsoscelesTrapeziod.h"
#include "CompositeShape.h"

void printInfo(const std::vector<std::unique_ptr<Shape>>& shapes)
{
  std::cout << std::fixed << std::setprecision(2);

  for (const auto& shape : shapes)
  {
    if (shape->getName() == "CompositeShape")
      continue;

    Point c = shape->getCenter();

    std::cout << "[" << shape->getName() << ", (" << c.x << ", " << c.y << "), "
      << shape->getArea() << "]" << std::endl;
  }
}

int main()
{
  try
  {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 2)));
    shapes.push_back(std::make_unique<Rectangle>(Point(1, 1), Point(3, 5)));

    shapes.push_back(std::make_unique<Ring>(Point(5, 5), 3, 1));
    shapes.push_back(std::make_unique<Ring>(Point(2, 7), 2, 0.5));

    shapes.push_back(std::make_unique<IsoscelesTrapeziod>(Point(0, 0), 6, 4, 3));

    auto composite = std::make_unique<CompositeShape>();

    composite->addShape(std::make_unique<Rectangle>(Point(0, 0), Point(1, 1)));
    composite->addShape(std::make_unique<Ring>(Point(2, 2), 2, 1));

    shapes.push_back(std::move(composite));

    printInfo(shapes);

    std::cout << "--- After scaling ---" << std::endl;

    for (auto& shape : shapes)
    {
      shape->scale(2.0);
    }

    printInfo(shapes);
  }
  catch (const std::exception& e)
  {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}

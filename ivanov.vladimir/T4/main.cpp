#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include "rectangle.h"
#include "circle.h"
#include "rectangle-trapezoid.h"
#include "composite-shape.h"

void printShape(const Shape& shape)
{
    Point c = shape.getCenter();
    const CompositeShape* comp = dynamic_cast<const CompositeShape*>(&shape);
    if (comp)
    {
        std::cout << "[COMPOSITE, (" << std::fixed << std::setprecision(2)
            << c.x << ", " << c.y << "), " << shape.getArea() << ":\n";
        for (size_t i = 0; i < comp->getSize(); ++i)
        {
            std::shared_ptr<Shape> inner = comp->getShape(i);
            Point ic = inner->getCenter();
            std::cout << inner->getName() << ", (" << std::fixed << std::setprecision(2)
                << ic.x << ", " << ic.y << "), " << inner->getArea() << ",\n";
        }
        std::cout << "]\n";
    }
    else
    {
        std::cout << "[" << shape.getName() << ", (" << std::fixed << std::setprecision(2)
            << c.x << ", " << c.y << "), " << shape.getArea() << "]\n";
    }
}

int main()
{
    try
    {
        auto r1 = std::make_shared<Rectangle>(Point{0.0, 0.0}, Point{2.0, 2.0});
        auto c1 = std::make_shared<Circle>(Point{15.0, 15.0}, 5.0);
        auto t1 = std::make_shared<RectangleTrapezoid>(Point{0.0, 0.0}, 4.0, 2.0, 2.0);
        auto r2 = std::make_shared<Rectangle>(Point{-2.0, -2.0}, Point{-1.0, -1.0});
        auto comp = std::make_shared<CompositeShape>();
        comp->addShape(r1);
        comp->addShape(c1);
        comp->addShape(t1);
        std::vector<std::shared_ptr<Shape>> shapes = {r1, c1, t1, r2, comp};
        for (const auto& s : shapes)
        {
            printShape(*s);
        }
        std::string cmd;
        if (!(std::cin >> cmd))
        {
            std::cerr << "Error: No scaling command provided\n";
            return 1;
        }
        double factor = 2.0;
        try
        {
            factor = std::stod(cmd);
        }
        catch (...)
        {
            if (cmd == "SCALE")
            {
                double cx, cy;
                if (!(std::cin >> cx >> cy >> factor))
                {
                    std::cerr << "Error: Invalid SCALE parameters\n";
                    return 1;
                }
            }
            else
            {
                std::cerr << "Error: Invalid input format\n";
                return 1;
            }
        }
        if (factor <= 0.0)
        {
            std::cerr << "Error: Scale factor must be positive\n";
            return 1;
        }
        std::cout << "\n";
        for (auto& s : shapes)
        {
            s->scale(factor);
            printShape(*s);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

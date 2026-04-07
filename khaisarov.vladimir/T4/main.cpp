#include "rectangle.h"
#include "ellipse.h"
#include "recttrapezoid.h"
#include "compositeshape.h"
#include <iostream>
#include <vector>
#include <memory>

template<class T>
void fillContainer(std::vector<std::unique_ptr<Shape>>& cont, T shape)
{
    cont.push_back(std::make_unique<T>(std::move(shape)));
}

void scaleInContainer(std::vector<std::unique_ptr<Shape>>& cont, double factor)
{
    if (cont.empty())
    {
        std::cout << "Container is empty, nothing to scale." << std::endl;
    }
    else
    {
        for (size_t i = 0; i < cont.size(); ++i)
        {
            cont[i]->scale(factor);
        }
    }
}

void printCont(const std::vector<std::unique_ptr<Shape>>& cont)
{
    if (cont.empty())
    {
        std::cout << "Container is empty, nothing to print." << std::endl;
    }
    else
    {
        for (size_t i = 0; i < cont.size(); ++i)
        {
            std::cout << *cont[i] << std::endl;
        }

    }
}

int main()
{
    try
    {
        std::vector<std::unique_ptr<Shape>> container;

        Point pr1(1, 1);
        Point pr2(-2, -2);
        Rectangle r1(pr1, pr2);
        fillContainer(container, r1);

        Rectangle r2(Point(2, 3), Point(-3, -5));
        fillContainer(container, r2);

        Point pe(0, 0);
        Ellipse e1(pe, 3, 4);
        fillContainer(container, e1);

        Point prt(1, 1);
        RectTrapezoid rt(prt, 4, 5, 3);
        fillContainer(container, rt);

        CompositeShape cs1;
        cs1.add(std::make_unique<RectTrapezoid>(Point(1, 1), 4, 5, 3));
        cs1.add(std::make_unique<Ellipse>(Point(2, 2), 3, 4));
        cs1.add(std::make_unique<Rectangle>(Point(0, 0), Point(10, 10)));
        fillContainer(container, std::move(cs1));

        printCont(container);

        double fact;
        if (!(std::cin >> fact) || fact <= 0)
        {
            std::cerr << "error!" << std::endl;
            return 0;
        }


        scaleInContainer(container, fact);

        printCont(container);
    }
    catch (const std::exception& e)
    {
        std::cerr << "error! " << e.what() << std::endl;
    }
    return 0;
}

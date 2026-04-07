#ifndef POINT
#define POINT
#include <iostream>
#include <memory>
#include <cstdlib>

class Point
{
public:
    double x;
    double y;
    Point() : x(0.00), y(0.00) {}
    Point(const double& x_, const double& y_) : x(x_), y(y_) {}
    Point(const Point& ot) : x(ot.x), y(ot.y) {}
    Point(Point&& ot) : x(ot.x), y(ot.y)
    {
        ot.x = 0;
        ot.y = 0;
    }
    ~Point() {}

    Point& operator=(const Point& ot)
    {
        if (this != &ot)
        {
            x = ot.x;
            y = ot.y;
        }
        return *this;
    }
    Point& operator=(Point&& ot)
    {
        if (this != &ot)
        {
            x = ot.x;
            y = ot.y;
            ot.x = 0;
            ot.y = 0;
        }
        return *this;
    }
    void print()
    {
        std::cout << "( " << x << " ; " << y << " )\n";
    }
};


#endif

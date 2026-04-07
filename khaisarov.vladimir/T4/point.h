#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <iomanip>

struct Point
{
    double x = 0.0;
    double y = 0.0;


    Point() = default;
    Point(double x_val, double y_val) : x(x_val), y(y_val) {}

    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        os << std::fixed << std::setprecision(2);
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

#endif

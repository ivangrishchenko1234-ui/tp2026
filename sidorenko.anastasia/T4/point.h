#ifndef POINT_H
#define POINT_H

struct Point
{
    double x = 0.0;
    double y = 0.0;
    Point() = default;
    Point(double c_x, double c_y) : x(c_x),
        y(c_y)
    {
    }
};

#endif

#include <iostream>

#ifndef POINT_H
#define POINT_H

struct Point {
    double x_, y_;

    Point() = default;
    Point(double x, double y) : x_(x), y_(y) { }
    ~Point() = default;
};

#endif // !POINT_H
